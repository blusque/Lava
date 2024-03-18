#pragma once
#include <glm/vec2.hpp>

#include "CollisionComponent.h"
#include "ParticleSystem.h"
#include "Lava/Core/Timestep.h"
#include "Lava/Events/Event.h"
#include "Lava/Events/KeyboardEvent.h"
#include "Lava/Renderer/Texture.h"

class Player
{
public:
    Player();
    ~Player();

    void OnBegin();
    void OnUpdate(Lava::Timestep ts);
    void OnGuiRender();
    void OnEvent(Lava::Event* e);

    glm::vec2 GetPosition() const { return m_Position; }
    float GetRotation() const { return m_Rotation; }
    glm::vec2 GetScale() const { return m_Scale; }
    Lava::Ref<Lava::Texture> GetTexture() const { return m_Texture; }
    Lava::Ref<ParticleSystemComponent> GetParticleSystem() const { return m_ParticleSystemComp; }
    Lava::Ref<CollisionComponent> GetCollision() const { return m_CollisionComp; }

private:
    bool OnKeyInput(Lava::KeyPressedEvent* e);

private:
    glm::vec2 m_Position { 0.f, 0.f };
    float m_Rotation { 0.f };
    
    glm::vec2 m_Velocity { 200.f, 0.f };
    float m_Gravity { 5.f };

    glm::vec2 m_Scale { 45.f, 80.f };
    Lava::Ref<Lava::Texture> m_Texture;

    bool b_IsUp { false };
    float m_Acc { 100.f };

    Lava::Ref<CollisionComponent> m_CollisionComp;
    Lava::Ref<ParticleSystemComponent> m_ParticleSystemComp;
    float m_IntervalTime { 0.12f };
    float m_AccumulateTime { 0.f };
};
