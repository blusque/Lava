#pragma once
#include "Lava/Debug/Instrumentor.h"

#ifdef LV_PLATFORM_WINDOWS

extern void Lava::RegisterApplication();

inline int main(int argc, char* argv[])
{
    Lava::Log::Init();
    LV_CORE_WARN("Hello Lava!");
    LV_INFO("Sandbox Start!");
    // auto app = Lava::CreateApplication();
    LV_PROFILE_BEGIN_SESSION("StartUp", "C:/Users/kokut/dev/Lava/Debug/Profile/StartUp.json");
    Lava::RegisterApplication();
    auto app = Lava::Application::Get();
    LV_PROFILE_END_SESSION();

    LV_INFO("Sandbox Start!");
    LV_PROFILE_BEGIN_SESSION("Running", "C:/Users/kokut/dev/Lava/Debug/Profile/Running.json");
    app->Run();
    LV_PROFILE_END_SESSION();

    LV_PROFILE_BEGIN_SESSION("Shutdown", "C:/Users/kokut/dev/Lava/Debug/Profile/Shutdown.json");
    delete app;
    LV_PROFILE_END_SESSION();
    return 0;
}

#endif
