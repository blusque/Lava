﻿#pragma once
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

        virtual void AlignSize(unsigned x, unsigned y, unsigned width, unsigned height) = 0;
        
        virtual void SwapColor(const glm::vec4& color) = 0;
        virtual void SwapBuffer() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vao, uint32_t count) = 0;

        static Platform GetPlatform();

        static Ref<RenderAPI> GetAPI();
    protected:
        RenderAPI() = default;
    };   
}
