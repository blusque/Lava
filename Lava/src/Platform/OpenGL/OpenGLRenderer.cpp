#include "lvpch.h"
#include "OpenGLRenderer.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>


namespace Lava
{
    void OpenGLRenderer::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::AlignSize(unsigned x, unsigned y, unsigned width, unsigned height)
    {
        glViewport(x, y, width, height);
    }


    void OpenGLRenderer::SwapColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderer::SwapBuffer()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::DrawIndexed(const Ref<VertexArray>& vao)
    {
        glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    OpenGLRenderer* OpenGLRenderer::GetAPI()
    {
        return new OpenGLRenderer;
    }

}
