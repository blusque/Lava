#pragma once

#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Lava/Renderer/RenderAPI.h"

namespace Lava
{
    class OpenGLRenderer: public RenderAPI
    {
    public:
        ~OpenGLRenderer() override = default;
        void Init() override;

        void AlignSize(unsigned x, unsigned y, unsigned width, unsigned height) override;
        
        void SwapColor(const glm::vec4& color) override;
        void SwapBuffer() override;

        void DrawIndexed(const Ref<VertexArray>& vao, uint32_t count) override;

        static OpenGLRenderer* GetAPI();
    private:
        OpenGLRenderer() = default;
    };
}
