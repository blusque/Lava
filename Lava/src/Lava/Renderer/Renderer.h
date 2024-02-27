#pragma once
#include "RenderAPI.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Lava/Camera.h"

namespace Lava
{
    class LAVA_API Renderer
    {
    public:
        static void BeginScene(const Camera::ptr& cam);

        static void Submit(const VertexArray::ptr& vao, const Shader::ptr& shader, const glm::mat4& transform = glm::mat4(1.f));
        
        static void EndScene();

        static std::shared_ptr<RenderAPI> GetAPI();

    private:
        static glm::mat4 m_VPMatrix;
    };
}

