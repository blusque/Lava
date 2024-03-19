#include "lvpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Lava
{
    glm::mat4 Renderer::m_VPMatrix = glm::mat4(1.f);

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

    void Renderer::ResizeCamera(unsigned width, unsigned height)
    {
        RenderCommand::AlignSize(0, 0, width, height);    
    }
    
    void Renderer::BeginScene(const Ref<Camera>& cam)
    {
        m_VPMatrix = cam->GetVPMatrix();
    }

    void Renderer::Submit(const Ref<VertexArray>& vao, const Ref<Shader>& shader, const glm::mat4& transform)
    {
        LV_PROFILE_FUNCTION();
        
        if (shader)
        {
            shader->Bind();
            shader->SetUniformMatrix4fv("u_VPMatrix", 1, false, &m_VPMatrix[0][0]);
            shader->SetUniformMatrix4fv("u_MMatrix", 1, false, &transform[0][0]);
        }
        if (vao)
        {
            vao->Bind();
            RenderCommand::DrawIndexed(vao);
        }
    }

    void Renderer::EndScene()
    {
        m_VPMatrix = glm::mat4(1.f);
    }

    RenderAPI::Platform Renderer::GetPlatform()
    {
        return RenderAPI::GetPlatform();
    }
}
