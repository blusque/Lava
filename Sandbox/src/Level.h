#pragma once

#include "Player.h"
#include "Lava/Core/Timestep.h"
#include "Lava/Events/Event.h"
#include "Lava/Renderer/Camera.h"

class Level
{
public:
    Level();
    ~Level() = default;
    void OnBegin();
    void OnUpdate(Lava::Timestep ts);
    void OnGuiRender();
    void OnEvent(Lava::Event* e);

private:
    Lava::Ref<Player> m_Player;
    std::vector<float> m_FloorPosition;
    Lava::Ref<Lava::Camera> m_Camera;
    Lava::Ref<Lava::CameraController> m_CameraController;
};
