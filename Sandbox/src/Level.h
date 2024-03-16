#pragma once

#include "Player.h"
#include "Lava/Core/Timestep.h"
#include "Lava/Events/Event.h"
#include "Lava/Renderer/Camera.h"

class Pillar;

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
    Lava::Ref<Pillar> CreatePillar(uint32_t index);
    void UpdatePillar();
    
private:
    Lava::Ref<Player> m_Player;
    std::vector<Lava::Ref<Pillar>> m_Pillars;
    Lava::Ref<Lava::Camera> m_Camera;
    Lava::Ref<Lava::CameraController> m_CameraController;
    float m_DistX { 30.f };
    float m_PosY { 30.f };
    float m_DeepZ { 0.1f };
    uint32_t m_PillarIndex { 0 };
    uint32_t m_PillarNum { 5 };
};
