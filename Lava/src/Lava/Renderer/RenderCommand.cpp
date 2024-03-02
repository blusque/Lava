#include "lvpch.h"
#include "RenderCommand.h"
#include "Renderer.h"

namespace Lava
{
    void RenderCommand::Init()
    {
        RenderAPI::GetAPI()->Init();    
    }
    
    void RenderCommand::SwapColor(const glm::vec4& color)
    {
        RenderAPI::GetAPI()->SwapColor(color);
    }

    void RenderCommand::SwapBuffer()
    {
        RenderAPI::GetAPI()->SwapBuffer();
    }

    void RenderCommand::DrawIndexed(const Ref<VertexArray>& vao)
    {
        RenderAPI::GetAPI()->DrawIndexed(vao);
    }
}
