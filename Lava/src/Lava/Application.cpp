#include "lvpch.h"
#include "Application.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"

namespace Lava
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        LV_CORE_ASSERT(!s_Instance, "There should be only one instance");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(1.f, 0.f, 1.f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto&& layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
            
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event* e)
    {
        auto dispatcher = EventDispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        // LV_CORE_INFO("{0}", *e);

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            (*it)->OnEvent(e);
            if (e->Handled())
            {
                break;
            }
        }
    }

    void Application::Push(Layer* layer)
    {
        m_LayerStack.Push(layer);
        layer->OnAttach();
    }

    void Application::PushBack(Layer* layer)
    {
        m_LayerStack.PushBack(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent* e)
    {
        m_Running = false;
        return true;
    }
}
