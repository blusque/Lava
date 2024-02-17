#pragma once

#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Lava/Renderer/RenderAPI.h"

namespace Lava
{
    class OpenGLRenderer: public RenderAPI
    {
    public:
        void SwapColor(const glm::vec4& color) override;
        void SwapBuffer() override;

        void DrawIndexed(const VertexArrayPtr& vao) override;
    };
}
