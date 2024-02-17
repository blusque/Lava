#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.h"

namespace Lava
{
    class RenderCommand
    {
    public:
        static void SwapColor(const glm::vec4& color);
        static void SwapBuffer();

        static void DrawIndexed(const VertexArrayPtr& vao);
    };   
}
