#pragma once
#include <memory>

namespace Lava
{
    class Texture
    {
    public:
        Texture(const char* textureFile);
        ~Texture();

        void Bind(int slot = 0) const;
        
    private:
        unsigned int m_Renderer;
        int m_Width;
        int m_Height;
        int m_Channels;
    };

    using TexturePtr = std::shared_ptr<Texture>;
    using TextureUPtr = std::unique_ptr<Texture>;
}
