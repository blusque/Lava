#include "Lava.h"

class ExampleLayer: public Lava::Layer
{
public:
    ExampleLayer() = default;
    ~ExampleLayer() {}

    void OnUpdate() const override
    {
        LV_INFO("Update");
    }

    void OnEvent(Lava::Event* e) const override
    {
        LV_TRACE("{0}", *e);
    }
};

class Sandbox: public Lava::Application
{
public:
    Sandbox() { m_LayerStack.PushBack(new ExampleLayer); }
    ~Sandbox() override = default;
};


Lava::Application* Lava::CreateApplication()
{
    return new Sandbox();
}
