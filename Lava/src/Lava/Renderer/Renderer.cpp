#include "lvpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Lava
{
    struct RendererStorage
    {
        glm::mat4 VMatrix;
        glm::mat4 PMatrix;
        glm::mat4 VPMatrix;
    };

    static auto s_Data = RendererStorage();

    void Renderer::Init()
    {
        LV_PROFILE_FUNCTION();
        
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    }

    void Renderer::ResizeViewport(uint32_t width, uint32_t height)
    {
        RenderCommand::AlignSize(0, 0, width, height);    
    }
    
    void Renderer::BeginScene(const Ref<Camera>& cam)
    {
        s_Data.VMatrix = cam->GetViewMatrix();
        s_Data.PMatrix = cam->GetProjMatrix();
        s_Data.VPMatrix = cam->GetVPMatrix();
    }

    void Renderer::Submit(const Ref<VertexArray>& vao, const Ref<Shader>& shader, const glm::mat4& transform)
    {
        LV_PROFILE_FUNCTION();
        
        if (shader)
        {
            shader->Bind();
            shader->SetUniformMatrix4fv("u_VMatrix", 1, false, &s_Data.VMatrix[0][0]);
            shader->SetUniformMatrix4fv("u_PMatrix", 1, false, &s_Data.PMatrix[0][0]);
            shader->SetUniformMatrix4fv("u_VPMatrix", 1, false, &s_Data.VPMatrix[0][0]);
            shader->SetUniformMatrix4fv("u_MMatrix", 1, false, &transform[0][0]);
            auto const normal = transpose(inverse(transform));
            shader->SetUniformMatrix4fv("u_NMatrix", 1, false, &normal[0][0]);
        }
        if (vao)
        {
            vao->Bind();
            RenderCommand::DrawIndexed(vao);
        }
    }

    void Renderer::Shadow(const Ref<Shader>& shader, const Ref<Framebuffer>& shadowBuffer,
        const glm::mat4& lightspaceTrans)
    {
        if (shader)
        {
            auto const shadowMapUS = TextureUnsafe::Create(shadowBuffer->GetDepth());
            shadowMapUS->Bind(31);
            shader->SetUniform1i("u_ShadowMap", 31);
            shader->SetUniformMatrix4fv("u_LightspaceVPMatrix", 1, false, &lightspaceTrans[0][0]);
        }
    }

    void Renderer::EndScene()
    {
        s_Data.VMatrix = glm::mat4(1.f);
        s_Data.PMatrix = glm::mat4(1.f);
        s_Data.VPMatrix = glm::mat4(1.f);
    }

    RenderAPI::Platform Renderer::GetPlatform()
    {
        return RenderAPI::GetPlatform();
    }
}
