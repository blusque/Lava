#include "lvpch.h"
#include "Application.h"

#include "Input.h"
#include <GLFW/glfw3.h>

// #include "glad/gl.h"
#include "Lava/Core/Timestep.h"
#include "Lava/Renderer/GraphicsContext.h"

#include "Lava/Renderer/Renderer.h"
#include "Lava/Renderer/RenderCommand.h"

namespace Lava
{
    Application* Application::s_Instance = nullptr;

    std::function<Application*()> Application::CreateApplication = []()
    {
        if (!s_Instance)
        {
            return new Application;
        }
        return s_Instance;
    };

    // Application* Application::Get()
    // {
    //     if (s_Instance)
    //     {
    //         s_Instance = CreateApplication();
    //     }
    //     return s_Instance;
    // }

    Application::Application()
        // TODO: find where to put this "new" line
    {
        LV_PROFILE_FUNCTION();
        
        LV_CORE_ASSERT(!s_Instance, "There should be only one instance")
        m_Window = Window::Create(GraphicsContextFactory::GetFactory().Create());
        m_Window->SetEventCallback(BIND_CLASS_EVENT(Application::OnEvent));

        m_GuiLayer = new ImGuiLayer;
    }

    void Application::OnBegin()
    {
        LV_PROFILE_FUNCTION();
        
        Renderer::Init();
        
        PushBack(m_GuiLayer);
    }

    void Application::Run()
    {
        LV_PROFILE_FUNCTION();
        
        this->OnBegin();

        m_LastFrameTime = static_cast<float>(glfwGetTime());
        while (m_Running)
        {
            auto const t = static_cast<float>(glfwGetTime());
            auto const ts = Timestep(t - m_LastFrameTime);
            m_LastFrameTime = t;

            if (!m_Minimized)
            {
                {
                    LV_PROFILE_SCOPE("LayerStack OnUpdate");
                    for (auto&& layer : m_LayerStack)
                    {
                        layer->OnUpdate(ts);
                    }
                }
            }
            
            m_GuiLayer->OnBegin();
            {
                LV_PROFILE_SCOPE("UI OnUpdate");
                for (auto&& layer : m_LayerStack)
                {
                    layer->OnGuiRender();
                }
            }
            m_GuiLayer->OnEnd();

            {
                LV_PROFILE_SCOPE("Window OnUpdate");
                m_Window->OnUpdate();
            }
        }
    }

    void Application::OnEvent(Event* e)
    {
        auto dispatcher = EventDispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_CLASS_EVENT(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_EVENT(Application::OnWindowResized));
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
        LV_PROFILE_FUNCTION();
        
        m_LayerStack.Push(layer);
        layer->OnAttach();
    }

    void Application::PushBack(Layer* layer)
    {
        LV_PROFILE_FUNCTION();
        
        m_LayerStack.PushBack(layer);
        layer->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent* e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResized(WindowResizeEvent* e)
    {
        if (!e->GetWidth() || !e->GetHeight())
        {
            m_Minimized = true;
        }
        m_Minimized = false;

        return false;
    }
}
