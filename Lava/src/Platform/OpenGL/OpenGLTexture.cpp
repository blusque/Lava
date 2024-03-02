#include "lvpch.h"
#include "OpenGLTexture.h"

#include <glad/gl.h>
#include "stb_image.h"

namespace Lava
{
    OpenGLTexture::OpenGLTexture(const char* textureFile)
    {
        LV_CORE_INFO("Texture Path: {0}", textureFile);
        stbi_set_flip_vertically_on_load(1);
        auto const tex = stbi_load(textureFile, &m_Width, &m_Height, &m_Channels, 0);
        LV_CORE_INFO("Texture Info: w: {0}, h: {1}, c: {2}", m_Width, m_Height, m_Channels);
        
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        auto internalFormat = 0;
        auto format = 0;
        if (m_Channels == 4)
        {
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
        }
        else if (m_Channels == 3)
        {
            internalFormat = GL_RGB8;
            format = GL_RGB;
        }
        // internalFormat = GL_RGBA8;
        // format = GL_RGBA;

        LV_CORE_ASSERT(internalFormat && format, "The channel num of the texture image has to be 3 or 4!")

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, tex);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture::Bind(int slot /*= 0*/) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
}
