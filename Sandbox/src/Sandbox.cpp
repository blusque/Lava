#include "Lava.h"

class ExampleLayer: public Lava::Layer
{
public:
    ExampleLayer() : Layer("Example Layer") {}
    ~ExampleLayer() = default;

    void OnUpdate() override
    {
        Layer::OnAttach();
        
        LV_INFO("Update");
    }

    void OnEvent(Lava::Event* e) override
    {
        Layer::OnEvent(e);
        
        LV_TRACE("{0}", *e);
    }
};

class Sandbox: public Lava::Application
{
public:
    Sandbox()
    {
        Push(new ExampleLayer);
        PushBack(new Lava::ImGuiLayer);
    }
    ~Sandbox() override = default;
};


Lava::Application* Lava::CreateApplication()
{
    return new Sandbox;
}
