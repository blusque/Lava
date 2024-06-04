#pragma once
#include <glm/vec4.hpp>

#include "VertexArray.h"

namespace Lava
{
    enum RendererBuffer
    {
        COLOR_BUFFER = BIT(0),
        DEPTH_BUFFER = BIT(1)
    };
    
    class LAVA_API RenderAPI
    {
    public:
        virtual ~RenderAPI() {}
        
        enum class Platform {
            None = 0, OpenGL = 1
        };

        virtual void Init() = 0;

        virtual void AlignSize(unsigned x, unsigned y, unsigned width, unsigned height) = 0;
        
        virtual void SwapColor(const glm::vec4& color) = 0;
        virtual void SwapBuffer(RendererBuffer buffer) = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vao, uint32_t count) = 0;

        static Platform GetPlatform();

        static Ref<RenderAPI> GetAPI();
    protected:
        RenderAPI() = default;
    };   
}
