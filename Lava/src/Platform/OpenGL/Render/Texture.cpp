#include "lvpch.h"
#include "Texture.h"

#include <glad/gl.h>
#include "stb_image.h"

namespace Lava
{
    Texture::Texture(const char* textureFile)
    {
        stbi_set_flip_vertically_on_load(1);
        auto const tex = stbi_load(textureFile, &m_Width, &m_Height, &m_Channels, 4);
        
        glGenTextures(1, &m_Renderer);
        glBindTexture(GL_TEXTURE_2D, m_Renderer);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_Renderer);
    }

    void Texture::Bind(int slot /*= 0*/) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_Renderer);
    }
}
