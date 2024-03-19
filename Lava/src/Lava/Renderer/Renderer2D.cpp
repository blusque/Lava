#include "lvpch.h"
#include "Renderer2D.h"

#include "Lava/Renderer/Shader.h"
#include "Lava/Renderer/VertexArray.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/ext/matrix_transform.hpp>

#include "RenderCommand.h"

namespace Lava
{
    
    struct QuadVertex
    {
        glm::vec3 Point;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
    };

    static constexpr uint32_t MaxQuads { 1024 };
    static constexpr uint32_t MaxVertices { 4 * MaxQuads };
    static constexpr uint32_t MaxIndices { 6 * MaxQuads };
    static constexpr uint32_t MaxTextures { 32 };
    
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<ShaderLibrary> ShaderLibrary;
        Ref<Texture> WhiteTexture;
        
        QuadVertex* QuadVerticesBase { nullptr };
        QuadVertex* QuadVerticesPtr { nullptr };
        uint32_t QuadIndicesCount { 0 };

        std::array<Ref<Texture>, MaxTextures> TextureSlots;
        uint32_t TextureIndex = 1;
    };
}

namespace 
{
    Lava::Renderer2DStorage* s_Data;
}

namespace Lava
{
    void Renderer2D::Init()
    {
        LV_PROFILE_FUNCTION();

        s_Data = new Renderer2DStorage;

        s_Data->ShaderLibrary = CreateRef<ShaderLibrary>();
        auto const TextureShader = Shader::Create();
        auto const texShaderProgram = Shader::ParseShaderProgram(ASSETS_PATH(shaders/Texture.glsl));
        TextureShader->Compile(texShaderProgram);
        s_Data->ShaderLibrary->Add(TextureShader);

        TextureShader->Bind();
        s_Data->WhiteTexture = Texture::Create(1, 1);
        auto data = 0xffffffff;
        s_Data->WhiteTexture->Bind();
        s_Data->WhiteTexture->SetData(&data, sizeof(uint32_t));
        
        s_Data->TextureSlots[0] = s_Data->WhiteTexture;

        int32_t samplers[MaxTextures];
        for (uint32_t i = 0; i < MaxTextures; i++)
        {
            samplers[i] = static_cast<int32_t>(i);
        }
        TextureShader->SetUniform1iv("u_TexSamplers", MaxTextures, samplers);
        
        s_Data->QuadVertexArray = VertexArray::Create();
        s_Data->QuadVerticesBase = new QuadVertex[MaxVertices];
        s_Data->QuadVertexBuffer = VertexBuffer::Create(nullptr, MaxVertices * sizeof(QuadVertex),
            BufferUseType::DYNAMIC);
        s_Data->QuadVertexBuffer->AddLayout(3, DataType::FLOAT, false);
        s_Data->QuadVertexBuffer->AddLayout(4, DataType::FLOAT, false);
        s_Data->QuadVertexBuffer->AddLayout(2, DataType::FLOAT, false);
        s_Data->QuadVertexBuffer->AddLayout(1, DataType::FLOAT, false);

        auto const indices = new uint32_t[MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < MaxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }
        auto const quadIBO = IndexBuffer::Create(indices,
            MaxIndices * sizeof(uint32_t), BufferUseType::STATIC);

        s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);
        s_Data->QuadVertexArray->SetIndexBuffer(quadIBO);
        delete[] indices;
    }

    void Renderer2D::Shutdown()
    {
        LV_PROFILE_FUNCTION();

        delete[] s_Data->QuadVerticesBase;
        s_Data->QuadVerticesBase = nullptr;
        s_Data->QuadVerticesPtr = nullptr;
        delete s_Data;
    }

    void Renderer2D::BeginScene(const Ref<Camera>& cam)
    {
        LV_PROFILE_FUNCTION();
        
        s_Data->ShaderLibrary->Get("Texture")->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
            "u_VPMatrix", 1, false, &cam->GetVPMatrix()[0][0]);
        s_Data->QuadVertexArray->Bind();
        
        s_Data->QuadVerticesPtr = s_Data->QuadVerticesBase;
        s_Data->QuadIndicesCount = 0;

        s_Data->TextureIndex = 1;
    }
    
    void Renderer2D::EndScene()
    {
        auto const size = static_cast<uint32_t>(reinterpret_cast<uint8_t*>(s_Data->QuadVerticesPtr) -
            reinterpret_cast<uint8_t*>(s_Data->QuadVerticesBase));
        s_Data->QuadVertexBuffer->BufferData(s_Data->QuadVerticesBase, size);
        
        for (uint32_t i = 0; i < s_Data->TextureIndex; i++)
        {
            s_Data->TextureSlots[i]->Bind(static_cast<int>(i));
        }
        
        Flush();
    }
    
    void Renderer2D::Flush()
    {
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->QuadIndicesCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data->QuadVerticesPtr->Point = { position.x - 0.5f * size.x,
            position.y - 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { position.x + 0.5f * size.x,
            position.y - 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 1.f, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { position.x + 0.5f * size.x,
            position.y + 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 1.f, 1.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { position.x - 0.5f * size.x,
            position.y + 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, 1.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadIndicesCount += 6;
        
        // auto TransMatrix = translate(glm::mat4(1.f), position)
        //     * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        // s_Data->ShaderLibrary->Get("Texture")->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
        //         "u_MMatrix", 1, false, &TransMatrix[0][0]);
        // s_Data->WhiteTexture->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1f("u_TillingFactor", 1.f);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
        //     "u_Color", color.r, color.g, color.b, color.a);
        //
        // s_Data->QuadVertexArray->Bind();
        // RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture,
        float tillingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({position.x, position.y, 0.f}, size, texture, tillingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture,
        float tillingFactor, const glm::vec4& tintColor)
    {
        float textureIndex = 0.f;

        for (uint32_t i = 1; i < s_Data->TextureIndex; i++)
        {
            if (*s_Data->TextureSlots[i] == *texture)
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.f)
        {
            textureIndex = static_cast<float>(s_Data->TextureIndex);
            s_Data->TextureSlots[s_Data->TextureIndex] = texture;
            s_Data->TextureIndex++;
        }
        
        s_Data->QuadVerticesPtr->Point = { position.x - 0.5f * size.x,
            position.y - 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;
        
        s_Data->QuadVerticesPtr->Point = { position.x + 0.5f * size.x,
            position.y - 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { tillingFactor, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;
        
        s_Data->QuadVerticesPtr->Point = { position.x + 0.5f * size.x,
            position.y + 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { tillingFactor, tillingFactor };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;
        
        s_Data->QuadVerticesPtr->Point = { position.x - 0.5f * size.x,
            position.y + 0.5f * size.y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, tillingFactor };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;
        
        s_Data->QuadIndicesCount += 6;
        
        // auto TransMatrix = translate(glm::mat4(1.f), position)
        //     * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        // s_Data->ShaderLibrary->Get("Texture")->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
        //         "u_MMatrix", 1, false, &TransMatrix[0][0]);
        // texture->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1f("u_TillingFactor", tillingFactor);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
        //     "u_Color", tintColor.r, tintColor.g, tintColor.b, tintColor.a);
        //
        // s_Data->QuadVertexArray->Bind();
        // RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size,
        const glm::vec4& color)
    {
        DrawRotateQuad({position.x, position.y, 0.f}, rotation, size, color);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size,
        const glm::vec4& color)
    {
        auto quad = std::vector<glm::vec2> {
            { -0.5f * size.x, -0.5f * size.y},
            {  0.5f * size.x, -0.5f * size.y},
            {  0.5f * size.x,  0.5f * size.y},
            { -0.5f * size.x,  0.5f * size.y},
        };
        
        auto rotMat = glm::mat2(1.f);
        rotMat[0][0] =  cos(rotation);
        rotMat[0][1] =  sin(rotation);
        rotMat[1][0] = -sin(rotation);
        rotMat[1][1] =  cos(rotation);

        for (auto&& vertex : quad)
        {
            vertex = rotMat * vertex;
            vertex.x = vertex.x + position.x;
            vertex.y = vertex.y + position.y;
        }
        
        s_Data->QuadVerticesPtr->Point = { quad[0].x, quad[0].y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { quad[1].x, quad[1].y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 1.f, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { quad[2].x, quad[2].y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 1.f, 1.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { quad[3].x, quad[3].y, position.z };
        s_Data->QuadVerticesPtr->Color = { color.r, color.g, color.b, color.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, 1.f };
        s_Data->QuadVerticesPtr->TexIndex = 0.f;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadIndicesCount += 6;
        
        // auto TransMatrix = translate(glm::mat4(1.f), position)
        //     * rotate(glm::mat4(1.f), rotation, {0.f, 0.f, 1.f})
        //     * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        // s_Data->ShaderLibrary->Get("Texture")->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
        //         "u_MMatrix", 1, false, &TransMatrix[0][0]);
        // s_Data->WhiteTexture->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
        //     "u_Color", color.r, color.g, color.b, color.a);
        //
        // s_Data->QuadVertexArray->Bind();
        // RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, float tillingFactor, const glm::vec4& tintColor)
    {
        DrawRotateQuad({position.x, position.y, 0.f}, rotation, size, texture, tillingFactor, tintColor);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, float tillingFactor, const glm::vec4& tintColor)
    {
        float textureIndex = 0.f;

        for (uint32_t i = 1; i < s_Data->TextureIndex; i++)
        {
            if (*s_Data->TextureSlots[i] == *texture)
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.f)
        {
            textureIndex = static_cast<float>(s_Data->TextureIndex);
            s_Data->TextureSlots[s_Data->TextureIndex] = texture;
            s_Data->TextureIndex++;
        }
        
        auto quad = std::vector<glm::vec2> {
                { -0.5f * size.x, -0.5f * size.y},
                {  0.5f * size.x, -0.5f * size.y},
                {  0.5f * size.x,  0.5f * size.y},
                { -0.5f * size.x,  0.5f * size.y},
            };
        
        auto rotMat = glm::mat2(1.f);
        rotMat[0][0] =  cos(rotation);
        rotMat[0][1] =  sin(rotation);
        rotMat[1][0] = -sin(rotation);
        rotMat[1][1] =  cos(rotation);

        for (auto&& vertex : quad)
        {
            vertex = rotMat * vertex;
            vertex.x = vertex.x + position.x;
            vertex.y = vertex.y + position.y;
        }

        s_Data->QuadVerticesPtr->Point = { quad[0].x, quad[0].y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { quad[1].x, quad[1].y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { tillingFactor, 0.f };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { quad[2].x, quad[2].y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { tillingFactor, tillingFactor };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadVerticesPtr->Point = { quad[3].x, quad[3].y, position.z };
        s_Data->QuadVerticesPtr->Color = { tintColor.r, tintColor.g, tintColor.b, tintColor.a };
        s_Data->QuadVerticesPtr->TexCoord = { 0.f, tillingFactor };
        s_Data->QuadVerticesPtr->TexIndex = textureIndex;
        s_Data->QuadVerticesPtr++;

        s_Data->QuadIndicesCount += 6;
        
        // auto TransMatrix = translate(glm::mat4(1.f), position)
        //     * rotate(glm::mat4(1.f), rotation, {0.f, 0.f, 1.f})
        //     * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        // s_Data->ShaderLibrary->Get("Texture")->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
        //         "u_MMatrix", 1, false, &TransMatrix[0][0]);
        // texture->Bind();
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform1f("u_TillingFactor", tillingFactor);
        // s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
        //     "u_Color", tintColor.r, tintColor.g, tintColor.b, tintColor.a);
        //
        // s_Data->QuadVertexArray->Bind();
        // RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}
