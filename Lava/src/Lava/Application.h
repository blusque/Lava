#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#define BIND_MEM_FUNC(x, ptr) std::bind(&(x), ptr, std::placeholders::_1)

namespace Lava
{
    class LAVA_API Application
    {
    public:
        Application();
        virtual ~Application(); // Note that with pre-declaring the classes that are wrapped with unique ptr later,
                                // you have to declare the destructor explicitly and implement it in *.cpp file,
                                // although the implementation will have no code.
                                // See https://www.jianshu.com/p/1a73d8a59781 for more details.

        virtual void Run();

        virtual void OnEvent(Event* e);

        void Push(Layer* layer);
        void PushBack(Layer* layer);

        Window* GetWindow() const { return m_Window.get(); }
        
        static Application* Get() { return s_Instance; }
    
    protected:
        bool OnWindowClose(WindowCloseEvent* e);
        
        WindowUPtr m_Window;
        bool m_Running { true };
        LayerStack m_LayerStack;
        ImGuiLayer* m_GuiLayer;

    private:
        static Application* s_Instance;

        std::shared_ptr<VertexBuffer> m_VBO;
        std::shared_ptr<IndexBuffer> m_IBO;
        std::shared_ptr<VertexArray> m_VAO;
    };

    Application* CreateApplication();
}
