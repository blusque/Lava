#pragma once
#include "Core.h"

namespace Lava
{
    class LAVA_API Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual void Run();
    };

    Application* CreateApplication();
}
