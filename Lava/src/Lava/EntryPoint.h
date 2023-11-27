#pragma once

#ifdef LV_PLATFORM_WINDOWS

extern Lava::Application* Lava::CreateApplication();

int main(int argc, char* argv[])
{
    Lava::Log::Init();
    LV_CORE_WARN("Hello Lava!");
    LV_INFO("Sandbox Start!");
    auto app = Lava::CreateApplication();
    app->Run();
    delete app;
    return 0;
}

#endif
