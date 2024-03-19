#include "lvpch.h"
#include "RenderCommand.h"
#include "Renderer.h"

namespace Lava
{
    void RenderCommand::Init()
    {
        LV_PROFILE_FUNCTION();
        
        RenderAPI::GetAPI()->Init();    
    }

    void RenderCommand::AlignSize(unsigned x, unsigned y, unsigned width, unsigned height)
    {
        LV_PROFILE_FUNCTION();
        
        RenderAPI::GetAPI()->AlignSize(x, y, width, height);
    }

    void RenderCommand::SwapColor(const glm::vec4& color)
    {
        LV_PROFILE_FUNCTION();
        
        RenderAPI::GetAPI()->SwapColor(color);
    }

    void RenderCommand::SwapBuffer()
    {
        LV_PROFILE_FUNCTION();
        
        RenderAPI::GetAPI()->SwapBuffer();
    }

    void RenderCommand::DrawIndexed(const Ref<VertexArray>& vao, uint32_t count)
    {
        LV_PROFILE_FUNCTION();
        
        RenderAPI::GetAPI()->DrawIndexed(vao, count);
    }
}
