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

    void OpenGLRenderer::DrawIndexed(const Ref<VertexArray>& vao, uint32_t count)
    {
        if (count == 0)
        {
            count = vao->GetIndexBuffer()->GetCount();
        }
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLRenderer* OpenGLRenderer::GetAPI()
    {
        return new OpenGLRenderer;
    }

}
