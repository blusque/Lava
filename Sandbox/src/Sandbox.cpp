#include "Lava.h"

class Sandbox: public Lava::Application
{
public:
    Sandbox() = default;
    ~Sandbox() override = default;

    void Run() override;
};

void Sandbox::Run()
{
    auto const e = Lava::WindowResizeEvent(1280, 960);
    if (e.GetEventType() == Lava::WindowResizeEvent::GetStaticType())
    {
        LV_TRACE(e);
        if (e.GetEventCategoryFlags() == Lava::EventCategoryApp)
        {
            LV_WARN(e);
        }
    }
    else
    {
        LV_ERROR(e);
    }

    while (true);
}


Lava::Application* Lava::CreateApplication()
{
    return new Sandbox();
}
