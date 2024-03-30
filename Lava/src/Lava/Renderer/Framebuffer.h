#pragma once
#include <glm/vec2.hpp>

namespace Lava
{
    struct FramebufferProps
    {
        int32_t Width;
        int32_t Height;
    };
    
    class LAVA_API Framebuffer
    {
    public:
        Framebuffer() = default;
        virtual ~Framebuffer() = default;
        
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Resize(glm::vec2 size) = 0;
        
        virtual uint32_t GetTexture() const = 0;
        virtual uint32_t GetDepth() const = 0;
        virtual glm::vec2 GetFramebufferSize() const = 0;
        
        static Ref<Framebuffer> Create(const FramebufferProps& props);
    };
}

