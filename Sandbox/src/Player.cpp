#include "Player.h"

#include <glm/common.hpp>
#include <glm/trigonometric.hpp>

#include "imgui.h"
#include "Lava/Core/Input.h"
#include "Lava/Core/KeyCodes.h"

Player::Player()
{
    m_Texture = Lava::Texture::Create("C:/Users/kokut/dev/Lava/Sandbox/assets/textures/SpaceShip.png");
}

Player::~Player()
{
}

void Player::OnBegin()
{
}

void Player::OnUpdate(Lava::Timestep ts)
{
    // Update Position
    m_Position += m_Velocity * static_cast<float>(ts);
    
    m_Rotation = atan2f(m_Velocity.y, m_Velocity.x);
    // m_Rotation = glm::radians(m_Velocity.y * 3.f);
    
    // Update Velocity
    if (b_IsUp)
    {
        m_Velocity.y += m_Acc;
        if (m_Velocity.y > 10.f)
        {
            b_IsUp = false; 
        }
    }
    else
    {
        m_Velocity.y -= m_Gravity;
    }
    m_Velocity = clamp(m_Velocity, -20.f, 20.f);
}

void Player::OnGuiRender()
{
    ImGui::Begin("Gravity & Acc");
    ImGui::SliderFloat("Gravity", &m_Gravity, 0.f, 1.f);
    ImGui::SliderFloat("Acc", &m_Acc, 0.f, 20.f);
    ImGui::End();
}

void Player::OnEvent(Lava::Event* e)
{
    auto dispatcher = Lava::EventDispatcher(e);

    dispatcher.Dispatch<Lava::KeyPressedEvent>(BIND_CLASS_EVENT(Player::OnKeyInput));
}

bool Player::OnKeyInput(Lava::KeyPressedEvent* e)
{
    if (e->GetKey() == LV_KEY_SPACE)
    {
        b_IsUp = true;
        return true; 
    }
    return false;
}
