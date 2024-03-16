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
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<ShaderLibrary> ShaderLibrary;
        Ref<Texture> WhiteTexture;
    };
}

namespace 
{
    Lava::Renderer2DStorage* s_Data = nullptr;
}

namespace Lava
{
    void Renderer2D::Init()
    {
        LV_PROFILE_FUNCTION();
        
        LV_ASSERT(s_Data == nullptr, "There should be only one s_Data instance!")
        s_Data = new Renderer2DStorage;
        
        float square[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0
        };

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
        
        s_Data->QuadVertexArray = VertexArray::Create();
        auto const SquVBO = VertexBuffer::Create(square, sizeof(square), BufferUseType::STATIC);
        SquVBO->AddLayout(3, DataType::FLOAT, false);
        SquVBO->AddLayout(2, DataType::FLOAT, false);
        
        auto const SquIBO = IndexBuffer::Create(indices, sizeof(indices), BufferUseType::STATIC);

        s_Data->QuadVertexArray->AddVertexBuffer(SquVBO);
        s_Data->QuadVertexArray->SetIndexBuffer(SquIBO);
    }

    void Renderer2D::Shutdown()
    {
        LV_PROFILE_FUNCTION();
        
        delete s_Data;
    }

    void Renderer2D::BeginScene(const Ref<Camera>& cam)
    {
        LV_PROFILE_FUNCTION();
        
        for (auto&& shader : *s_Data->ShaderLibrary)
        {
            shader.second->Bind();
            shader.second->SetUniformMatrix4fv("u_VPMatrix", 1, false, &cam->GetVPMatrix()[0][0]);
        }
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        auto TransMatrix = translate(glm::mat4(1.f), position)
            * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        s_Data->ShaderLibrary->Get("Texture")->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
                "u_MMatrix", 1, false, &TransMatrix[0][0]);
        s_Data->WhiteTexture->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1f("u_TillingFactor", 1.f);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
            "u_Color", color.r, color.g, color.b, color.a);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture,
        float tillingFactor, const glm::vec4& tintColor)
    {
        DrawQuad({position.x, position.y, 0.f}, size, texture, tillingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture,
        float tillingFactor, const glm::vec4& tintColor)
    {
        auto TransMatrix = translate(glm::mat4(1.f), position)
            * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        s_Data->ShaderLibrary->Get("Texture")->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
                "u_MMatrix", 1, false, &TransMatrix[0][0]);
        texture->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1f("u_TillingFactor", tillingFactor);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
            "u_Color", tintColor.r, tintColor.g, tintColor.b, tintColor.a);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size,
        const glm::vec4& color)
    {
        DrawRotateQuad({position.x, position.y, 0.f}, rotation, size, color);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size,
        const glm::vec4& color)
    {
        auto TransMatrix = translate(glm::mat4(1.f), position)
            * rotate(glm::mat4(1.f), rotation, {0.f, 0.f, 1.f})
            * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        s_Data->ShaderLibrary->Get("Texture")->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
                "u_MMatrix", 1, false, &TransMatrix[0][0]);
        s_Data->WhiteTexture->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
            "u_Color", color.r, color.g, color.b, color.a);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2& position, float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, float tillingFactor, const glm::vec4& tintColor)
    {
        DrawRotateQuad({position.x, position.y, 0.f}, rotation, size, texture, tillingFactor, tintColor);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3& position, float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, float tillingFactor, const glm::vec4& tintColor)
    {
        auto TransMatrix = translate(glm::mat4(1.f), position)
            * rotate(glm::mat4(1.f), rotation, {0.f, 0.f, 1.f})
            * scale(glm::mat4(1.f), { size.x, size.y, 1.f});
        s_Data->ShaderLibrary->Get("Texture")->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniformMatrix4fv(
                "u_MMatrix", 1, false, &TransMatrix[0][0]);
        texture->Bind();
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1i("u_TexSampler", 0);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform1f("u_TillingFactor", tillingFactor);
        s_Data->ShaderLibrary->Get("Texture")->SetUniform4f(
            "u_Color", tintColor.r, tintColor.g, tintColor.b, tintColor.a);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
    
    void Renderer2D::EndScene()
    {
    }
}
