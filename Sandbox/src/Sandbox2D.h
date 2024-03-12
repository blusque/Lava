#pragma once

#include <Lava.h>

#define ASSETS_ROOT "C:/Users/kokut/dev/Lava/Sandbox/assets/"
#define ASSETS_FILE(x) LV_STR(x)
#define ASSETS_PATH(x) LV_CONCAT(ASSETS_ROOT, ASSETS_FILE(x))

class Sandbox2D: public Lava::Layer
{
public:
    Sandbox2D()
        : Layer("Sandbox2D Layer")
        , m_Camera(Lava::Camera::Create({ 1920.f / 1080.f, 1.f }))
        , m_CameraController(Lava::CameraController::Create(m_Camera))
    {
    }
    ~Sandbox2D() override = default;

    void OnAttach() override;

    void OnDetach() override;

    void OnUpdate(Lava::Timestep ts) override;

    void OnEvent(Lava::Event* e) override;

    void OnGuiRender() override;

private:
    Lava::Ref<Lava::Texture> m_Texture;
    Lava::Ref<Lava::Camera> m_Camera;
    Lava::Ref<Lava::CameraController> m_CameraController;

    glm::vec4 m_SquColor { 0.2f, 0.3f, 0.8f, 1.f };
};
