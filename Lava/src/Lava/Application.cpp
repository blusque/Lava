#include "lvpch.h"
#include "Application.h"

#include "Input.h"
#include <GLFW/glfw3.h>

// #include "glad/gl.h"
#include "Lava/Core/Timestep.h"
#include "Renderer/GraphicsContext.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Lava
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
        // TODO: find where to put this "new" line
    {
        LV_CORE_ASSERT(!s_Instance, "There should be only one instance")
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create(GraphicsContextFactory::GetFactory().Create()));
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_GuiLayer = new ImGuiLayer;
        PushBack(m_GuiLayer);
    }

    Application::~Application() = default;

    void Application::Run()
    {
        while (m_Running)
        {
            auto const t = static_cast<float>(glfwGetTime());
            auto const ts = Timestep(t - m_LastFrameTime);
            m_LastFrameTime = t;
            
            for (auto&& layer : m_LayerStack)
            {
                layer->OnUpdate(ts);
            }

            m_GuiLayer->OnBegin();
            for (const auto& layer : m_LayerStack)
            {
                layer->OnGuiRender();
            }
            m_GuiLayer->OnEnd();
            
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
