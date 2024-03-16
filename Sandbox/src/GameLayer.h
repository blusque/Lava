#pragma once
#include "Lava.h"
#include "Level.h"
#include "Player.h"

class GameLayer: public Lava::Layer
{
public:
    GameLayer();
    ~GameLayer() override;

    void OnAttach() override;
    void OnUpdate(Lava::Timestep ts) override;
    void OnGuiRender() override;
    void OnEvent(Lava::Event* e) override;
    void OnDetach() override;

private:
    Lava::Ref<Level> m_Level;
    Lava::Ref<Lava::Camera> m_Camera;
    Lava::Ref<Lava::CameraController> m_CameraController;
};
