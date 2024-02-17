#include "lvpch.h"
#include "RenderCommand.h"
#include "Renderer.h"

namespace Lava
{
    void RenderCommand::SwapColor(const glm::vec4& color)
    {
        Renderer::GetAPI()->SwapColor(color);
    }

    void RenderCommand::SwapBuffer()
    {
        Renderer::GetAPI()->SwapBuffer();
    }

    void RenderCommand::DrawIndexed(const VertexArrayPtr& vao)
    {
        Renderer::GetAPI()->DrawIndexed(vao);
    }
}
