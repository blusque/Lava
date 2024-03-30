#include "lvpch.h"
#include "OpenGLFramebuffer.h"

#include "glad/gl.h"

namespace Lava
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferProps& props)
    {
        m_FramebufferProps = props;

        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(glm::vec2 size)
    {
        // LV_CORE_TRACE("Size: {0}, {1}", size.x, size.y);
        m_FramebufferProps.Width = static_cast<int32_t>(size.x);
        m_FramebufferProps.Height = static_cast<int32_t>(size.y);

        Invalidate();
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteTextures(1, &m_Texture);
            glDeleteTextures(1, &m_Depth);
            glDeleteFramebuffers(1, &m_RendererID);
        }
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
        glTextureStorage2D(m_Texture, 1, GL_RGB8, m_FramebufferProps.Width, m_FramebufferProps.Height);
        glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_Depth);
        glTextureStorage2D(m_Depth, 1, GL_DEPTH24_STENCIL8, m_FramebufferProps.Width, m_FramebufferProps.Height);

        glCreateFramebuffers(1, &m_RendererID);
        glNamedFramebufferTexture(m_RendererID, GL_COLOR_ATTACHMENT0, m_Texture, 0);
        glNamedFramebufferTexture(m_RendererID, GL_DEPTH_ATTACHMENT, m_Depth, 0);

        LV_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete!")
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
