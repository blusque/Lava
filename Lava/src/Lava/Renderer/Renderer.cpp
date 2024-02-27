#include "lvpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Lava
{
    glm::mat4 Renderer::m_VPMatrix = glm::mat4(1.f);
    
    void Renderer::BeginScene(const Camera::ptr& cam)
    {
        m_VPMatrix = cam->GetVPMatrix();
    }

    void Renderer::Submit(const VertexArray::ptr& vao, const Shader::ptr& shader, const glm::mat4& transform)
    {
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

    std::shared_ptr<RenderAPI> Renderer::GetAPI()
    {
        static std::shared_ptr<RenderAPI> api = nullptr;
        
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::None: LV_CORE_ERROR("A render API should be specific, now is None"); break;
        case RenderAPI::API::OpenGL: api = std::make_shared<OpenGLRenderer>(); break;
        default: LV_CORE_ERROR("Wrong API type!");
        }
            
        
        return api;
    }
}
