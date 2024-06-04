#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.h"
#include "RenderAPI.h"

namespace Lava
{
    class LAVA_API RenderCommand
    {
    public:
        static void Init();

        static void AlignSize(unsigned x, unsigned y, unsigned width, unsigned height);
        
        static void SwapColor(const glm::vec4& color);
        static void SwapBuffer(int32_t buffer = COLOR_BUFFER | DEPTH_BUFFER);

        static void DrawIndexed(const Ref<VertexArray>& vao, uint32_t count = 0);
    };   
}
