#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

#define BIND_MEM_FUNC(x, ptr) std::bind(&(x), ptr, std::placeholders::_1)

namespace Lava
{
    class LAVA_API Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual void Run();

        virtual void OnEvent(Event* e);

        virtual void Push(Layer* layer);
        virtual void PushBack(Layer* layer);

    protected:
        virtual bool OnWindowClose(WindowCloseEvent* e);
        
        WindowUPtr m_Window;
        bool m_Running { true };
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}
