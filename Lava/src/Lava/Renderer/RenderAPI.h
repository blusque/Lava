#pragma once
#include <glm/vec4.hpp>
#include "VertexArray.h"

namespace Lava
{
    class LAVA_API RenderAPI
    {
    public:
        virtual ~RenderAPI() {}
        
        enum class Platform {
            None = 0, OpenGL = 1
        };

        virtual void Init() = 0;
        
        virtual void SwapColor(const glm::vec4& color) = 0;
        virtual void SwapBuffer() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vao) = 0;

        static Platform GetPlatform();

        static Ref<RenderAPI> GetAPI();
    protected:
        RenderAPI() = default;
    };   
}
