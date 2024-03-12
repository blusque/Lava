#pragma once
#include "Lava/Renderer/Texture.h"

namespace Lava
{
    class OpenGLTexture: public Texture
    {
    public:
        OpenGLTexture(const char* textureFile);
        OpenGLTexture(uint32_t width, uint32_t height);
        ~OpenGLTexture() override;

        void Bind(int slot = 0) const override;

        void SetData(void* data, uint32_t size) const override;

    private:
        uint32_t m_DataFormat { 0 };
        uint32_t m_InternalFormat { 0 };
    };
}
