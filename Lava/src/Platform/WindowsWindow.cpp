#include "lvpch.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"

namespace Lava
{
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
        : s_GLFWInitialized(false)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.title;
        m_Data.Width = props.width;
        m_Data.Height = props.height;
        
        if (!s_GLFWInitialized)
        {
            auto const success = glfwInit();
            LV_ASSERT(success, "GLFW Initialize Failed!")
            s_GLFWInitialized = true;
        }
        LV_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
        m_Window = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    int WindowsWindow::GetWidth() const
    {
        return m_Data.Width;
    }

    int WindowsWindow::GetHeight() const
    {
        return m_Data.Height;
    }

    void WindowsWindow::SetEventCallback(const EventFn& callback)
    {
        m_Data.CallbackFn = callback;
    }

    void WindowsWindow::SetVSync(bool enable)
    {
        if (enable)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enable;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}
