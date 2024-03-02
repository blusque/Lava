﻿#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.h"

namespace Lava
{
    class LAVA_API RenderCommand
    {
    public:
        static void Init();
        
        static void SwapColor(const glm::vec4& color);
        static void SwapBuffer();

        static void DrawIndexed(const Ref<VertexArray>& vao);
    };   
}
