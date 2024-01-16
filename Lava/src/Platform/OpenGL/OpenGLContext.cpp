#include "lvpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Lava
{
    void OpenGLContext::Init(void* window)
    {
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(window));
        auto const version = gladLoadGL(glfwGetProcAddress);
        if (version == 0) {
            LV_CORE_FATAL("Failed to initialize OpenGL context\n");
            __debugbreak();
        }

        // Successfully loaded OpenGL
        LV_CORE_INFO("Loaded OpenGL {0}.{1}\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    }

    void OpenGLContext::SwapBuffers(void* window)
    {
        glfwSwapBuffers(static_cast<GLFWwindow*>(window));
    }

    IGraphicsContext* OpenGLContextFactory::CreateGraphicsContext()
    {
        return new OpenGLContext;
    }
}

