#include "lvpch.h"
#include "OpenGLRenderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>


namespace Lava
{
    // void OpenGLRenderer::Init()
    // {
    //     auto const version = gladLoadGL(glfwGetProcAddress);
    //     printf("GL: %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    //
    //     glEnable(GL_CULL_FACE);
    //     glEnable(GL_DEPTH_TEST);
    //     glDepthFunc(GL_LESS);
    //
    //     glEnable(GL_BLEND);
    //     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //
    //     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // }
    //
    // void Renderer::Render(int count)
    // {
    //     glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    // }
    //
    // void Renderer::PloygonMode(bool enable)
    // {
    //     if (enable)
    //     {
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //     }
    //     else
    //     {
    //         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //     }
    // }

    void OpenGLRenderer::SwapColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderer::SwapBuffer()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawIndexed(const VertexArrayPtr& vao)
    {
        glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
