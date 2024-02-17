#include "lvpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Lava
{
    void Renderer::BeginScene()
    {
        
    }

    void Renderer::Submit(const VertexArrayPtr& vao)
    {
        if (vao)
        {
            RenderCommand::DrawIndexed(vao);
        }
    }

    void Renderer::EndScene()
    {
        
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
