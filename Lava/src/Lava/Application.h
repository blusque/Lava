#pragma once
#include "Core.h"
#include "Window.h"

namespace Lava
{
    class LAVA_API Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual void Run();

    private:
        WindowUPtr m_Window;
        bool m_Running { true };
    };

    Application* CreateApplication();
}
