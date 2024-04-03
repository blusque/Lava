#include "lvpch.h"
#include "OpenGLTexture.h"

#include <glad/gl.h>
#include "stb_image.h"

namespace Lava
{
    OpenGLTexture::OpenGLTexture(const char* textureFile)
    {
        LV_PROFILE_FUNCTION();
        
        LV_CORE_INFO("Texture Path: {0}", textureFile);
        stbi_set_flip_vertically_on_load(1);
        auto const tex = stbi_load(textureFile, &m_Width, &m_Height, &m_Channels, 0);
        LV_CORE_INFO("Texture Info: w: {0}, h: {1}, c: {2}", m_Width, m_Height, m_Channels);
        
        if (m_Channels == 4)
        {
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
        }
        else if (m_Channels == 3)
        {
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        }
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // internalFormat = GL_RGBA8;
        // format = GL_RGBA;

        LV_CORE_ASSERT(m_InternalFormat && m_DataFormat, "The channel num of the texture image has to be 3 or 4!")

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, tex);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(tex);
    }

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
    {
        LV_PROFILE_FUNCTION();
        
        m_Width = static_cast<int>(width);
        m_Height = static_cast<int>(height);
        
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        LV_PROFILE_FUNCTION();
        
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture::Bind(int slot /*= 0*/) const
    {
        // glActiveTexture(GL_TEXTURE0 + slot);
        glBindTextureUnit(slot, m_RendererID);
    }

    void OpenGLTexture::SetData(void* data, uint32_t size) const
    {
        LV_PROFILE_FUNCTION();
        
        auto const bpp = static_cast<uint32_t>(m_DataFormat == GL_RGBA ? 4 : 3);
        LV_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data size should be width * height * bpp!")
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    float OpenGLTexture::GetWidth() const
    {
        return static_cast<float>(m_Width);
    }

    float OpenGLTexture::GetHeight() const
    {
        return static_cast<float>(m_Height);
    }

    uint32_t OpenGLTexture::GetRendererID() const
    {
        return m_RendererID;
    }

    bool OpenGLTexture::operator==(Texture& other) const
    {
        return this->m_RendererID == dynamic_cast<OpenGLTexture&>(other).m_RendererID;
    }
}
