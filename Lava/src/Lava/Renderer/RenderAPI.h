#pragma once
#include <glm/vec4.hpp>
#include "VertexArray.h"

namespace Lava
{
    class LAVA_API RenderAPI
    {
    public:
        enum class API {
            None = 0, OpenGL = 1
        };

        virtual void SwapColor(const glm::vec4& color) = 0;
        virtual void SwapBuffer() = 0;

        virtual void DrawIndexed(const VertexArray::ptr& vao) = 0;

        static API GetAPI()
        {
            static API s_API = API::OpenGL;
            return s_API;
        }
    };   
}
