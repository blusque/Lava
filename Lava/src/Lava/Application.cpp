#include "lvpch.h"
#include "Application.h"

#include "Input.h"
#include <GLFW/glfw3.h>

#include "glad/gl.h"
#include "Renderer/GraphicsContext.h"

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

namespace Lava
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
        // TODO: find where to put this "new" line
        : m_VBO(nullptr)
        , m_IBO(nullptr)
        , m_VAO(nullptr)
    {
        LV_CORE_ASSERT(!s_Instance, "There should be only one instance")
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create(GraphicsContextFactory::GetFactory().Create()));
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_GuiLayer = new ImGuiLayer;
        PushBack(m_GuiLayer);
        
        float triangle[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        unsigned int indices[] = {
            0, 1, 2
        };
        
        m_VAO.reset(VertexArray::Create());
        
        m_VBO.reset(VertexBuffer::Create(triangle, sizeof(triangle), BufferUseType::STATIC));
        m_VBO->AddLayout(3, DataType::FLOAT, false);

        m_IBO.reset(IndexBuffer::Create(indices, sizeof(indices), BufferUseType::STATIC));

        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(m_IBO);
    }

    Application::~Application() = default;

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SwapColor({ 0.f, 0.f, 1.f, 1.f });
            RenderCommand::SwapBuffer();

            Renderer::BeginScene();
            
            m_VAO->Bind();
            Renderer::Submit(m_VAO);
            // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            Renderer::EndScene();

            m_VAO->Bind();
            // Renderer::Render(3);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (auto&& layer : m_LayerStack)
            {
                layer->OnUpdate();
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
