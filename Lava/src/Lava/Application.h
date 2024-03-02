#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

#define BIND_MEM_FUNC(x, ptr) std::bind(&(x), ptr, std::placeholders::_1)

namespace Lava
{
    class LAVA_API Application
    {
    public:
        virtual ~Application() = default; // Note that with pre-declaring the classes that are wrapped with unique ptr later,
                                // you have to declare the destructor explicitly and implement it in *.cpp file,
                                // although the implementation will have no code.
                                // See https://www.jianshu.com/p/1a73d8a59781 for more details.

        void Run();

        virtual void OnEvent(Event* e);

        void Push(Layer* layer);
        void PushBack(Layer* layer);

        Window* GetWindow() const { return m_Window.get(); }
        
        static Application* Get()
        {
            if (!s_Instance)
            {
                s_Instance = CreateApplication();
            }
            return s_Instance;
        }

        template <typename T, typename... Args >
        static void Register(Args&&... args)
        {
            CreateApplication = [&]()
            {
                if (!s_Instance)
                {
                    return new T(std::forward<Args>(args)...);
                }
                return dynamic_cast<T*>(s_Instance);
            };
        }

    protected:
        Application();

        virtual void OnBegin();
        
        bool OnWindowClose(WindowCloseEvent* e);

    protected:
        Scope<Window> m_Window;
        bool m_Running { true };
        LayerStack m_LayerStack;
        ImGuiLayer* m_GuiLayer;
        // float m_Timestep;
        float m_LastFrameTime;

    private:
        static std::function<Application*()> CreateApplication;
        static Application* s_Instance;
    };

    // Application* CreateApplication();
    void RegisterApplication();
}
