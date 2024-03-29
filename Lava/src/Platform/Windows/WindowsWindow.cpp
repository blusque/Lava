﻿#include "lvpch.h"
#include "WindowsWindow.h"

#ifdef LV_PLATFORM_WINDOWS
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "Lava/Events/ApplicationEvent.h"
#include "Lava/Events/KeyboardEvent.h"
#include "Lava/Events/MouseEvent.h"
#include "Lava/Renderer/GraphicsContext.h"

namespace Lava
{
    bool WindowsWindow::s_GLFWInitialized = false;

    void GLFWErrorCallback(int error_code, const char* description)
    {
        LV_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
    }
    
    Scope<Window> Window::Create(IGraphicsContext* graphicsContext, const WindowProps& props)
    {
        LV_PROFILE_FUNCTION();
        
        return CreateScope<WindowsWindow>(props, graphicsContext);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props, IGraphicsContext* graphicsContext)
    {
        LV_PROFILE_FUNCTION();
        
        Init(props, graphicsContext);
    }

    WindowsWindow::~WindowsWindow()
    {
        LV_PROFILE_FUNCTION();
        
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props, IGraphicsContext* graphicsContext)
    {
        m_Data.Title = props.title;
        m_Data.Width = props.width;
        m_Data.Height = props.height;

        m_Context.reset(graphicsContext);
        
        if (!s_GLFWInitialized)
        {
            auto const success = glfwInit();
            LV_ASSERT(success, "GLFW Initialize Failed!")
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        LV_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
        m_Window = glfwCreateWindow(props.width, props.height, props.title, nullptr, nullptr);

        m_Context->Init(m_Window);

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
                    auto e = KeyReleasedEvent(key, mods);
                    data->CallbackFn(&e);
                    break;
                }
            case GLFW_PRESS:
                {
                    auto e = KeyPressedEvent(key, 0, mods);
                    data->CallbackFn(&e);
                    break;
                }
            case GLFW_REPEAT:
                {
                    auto e = KeyPressedEvent(key, 1, mods);
                    data->CallbackFn(&e);
                    break;
                }
            default:
                break;        
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            auto e = KeyTypedEvent(keycode);
            data->CallbackFn(&e);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            auto const data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_RELEASE:
                {
                    auto e = MouseButtonReleasedEvent(button, mods);
                    data->CallbackFn(&e);
                    break;
                }
            case GLFW_PRESS:
                {
                    auto e = MouseButtonPressedEvent(button, mods);
                    data->CallbackFn(&e);
                    break;
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
        m_Context->SwapBuffers(m_Window);
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
        LV_PROFILE_FUNCTION();
        
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

    void* WindowsWindow::GetNativeWindow() const
    {
        return m_Window;
    }
}

#endif