#pragma once
#include <glm/vec2.hpp>

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

private:
    bool OnKeyInput(Lava::KeyPressedEvent* e);

private:
    glm::vec2 m_Position { 0.f, 0.f };
    float m_Rotation { 0.f };
    
    glm::vec2 m_Velocity { 20.f, 0.f };
    float m_Gravity { 0.3f };

    glm::vec2 m_Scale { 1.8f, 3.2f };
    Lava::Ref<Lava::Texture> m_Texture;

    bool b_IsUp { false };
    float m_Acc { 5.f };
};
