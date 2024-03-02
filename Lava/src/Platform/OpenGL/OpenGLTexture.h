#pragma once
#include "Lava/Renderer/Texture.h"

namespace Lava
{
    class OpenGLTexture: public Texture
    {
    public:
        OpenGLTexture(const char* textureFile);
        ~OpenGLTexture() override;

        void Bind(int slot = 0) const override;
    };
}
