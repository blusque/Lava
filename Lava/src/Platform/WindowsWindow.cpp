#include "lvpch.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"
#include "Lava/Events/ApplicationEvent.h"
#include "Lava/Events/KeyboardEvent.h"
#include "Lava/Events/MouseEvent.h"

namespace Lava
{

    void GLFWErrorCallback(int error_code, const char* description)
    {
        LV_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
    }
    
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
        Shutdown();
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
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        LV_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
        m_Window = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            auto e = WindowResizeEvent(width, height);
            data->CallbackFn(&e);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            auto e = WindowCloseEvent();
            data->CallbackFn(&e);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_RELEASE:
                {
                    auto e = KeyReleasedEvent(key);
                    data->CallbackFn(&e);
                }
            case GLFW_PRESS:
                {
                    auto e = KeyPressedEvent(key, 0);
                    data->CallbackFn(&e);
                }
            case GLFW_REPEAT:
                {
                    auto e = KeyPressedEvent(key, 1);
                    data->CallbackFn(&e);
                }
            default:
                break;        
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_RELEASE:
                {
                    auto e = MouseButtonReleasedEvent(button);
                    data->CallbackFn(&e);
                }
            case GLFW_PRESS:
                {
                    auto e = MouseButtonPressedEvent(button);
                    data->CallbackFn(&e);
                }
            default:
                break;        
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            auto e = MouseScrolledEvent(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data->CallbackFn(&e);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            auto e = MouseMoveEvent(static_cast<float>(xPos), static_cast<float>(yPos));
            data->CallbackFn(&e);
        });
    }

    void WindowsWindow::Shutdown() const
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
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
