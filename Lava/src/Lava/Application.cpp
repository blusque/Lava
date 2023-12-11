#include "lvpch.h"
#include "Application.h"

#include <GL/gl.h>

namespace Lava
{
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1.f, 0.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }
}
