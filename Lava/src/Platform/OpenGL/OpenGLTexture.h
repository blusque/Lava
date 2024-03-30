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

        float GetWidth() const override;
        float GetHeight() const override;
        uint32_t GetRendererID() const override;

        bool operator ==(Texture& other) const override;

    private:
        uint32_t m_RendererID { 0 };
        uint32_t m_DataFormat { 0 };
        uint32_t m_InternalFormat { 0 };
    };
}
