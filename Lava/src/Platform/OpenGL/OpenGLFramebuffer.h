#pragma once

#include "Lava/Renderer/Framebuffer.h"

namespace Lava
{
    class OpenGLFramebuffer: public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferProps& props);
        ~OpenGLFramebuffer() override;

        void Bind() override;
        void Unbind() override;
        void Resize(glm::vec2 size) override;

        uint32_t GetTexture() const override { return m_Texture; }
        uint32_t GetDepth() const override { return m_Depth; }
        glm::vec2 GetFramebufferSize() const override
        {
            return {
                static_cast<float>(m_FramebufferProps.Width),
                static_cast<float>(m_FramebufferProps.Height)
            };
        }

    private:
        void Invalidate();
        
    private:
        uint32_t m_RendererID;
        uint32_t m_Texture;
        uint32_t m_Depth;
        FramebufferProps m_FramebufferProps;
    };
}
