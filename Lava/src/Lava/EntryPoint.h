#pragma once

#ifdef LV_PLATFORM_WINDOWS

extern void Lava::RegisterApplication();

inline int main(int argc, char* argv[])
{
    Lava::Log::Init();
    LV_CORE_WARN("Hello Lava!");
    LV_INFO("Sandbox Start!");
    // auto app = Lava::CreateApplication();
    Lava::RegisterApplication();
    auto app = Lava::Application::Get();
    LV_INFO("Sandbox Start!");
    app->Run();
    delete app;
    return 0;
}

#endif
