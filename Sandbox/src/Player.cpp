#include "Player.h"

#include <glm/common.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "imgui.h"
#include "Random.h"
#include "Lava/Core/Input.h"
#include "Lava/Core/KeyCodes.h"

Player::Player()
{
    m_Texture = Lava::Texture::Create("C:/Users/kokut/dev/Lava/Sandbox/assets/textures/SpaceShip.png");

    m_ParticleSystemComp = Lava::CreateRef<ParticleSystemComponent>();
    auto const collidePoints = std::vector<glm::vec2>{
        { -11.f,  35.f },
        {  11.f,  35.f },
        {  11.f, -35.f },
        { -11.f, -35.f }
    };
    m_CollisionComp = Lava::CreateRef<CollisionComponent>(CollisionComponent::PolygonType::Square, collidePoints);
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
    
    m_Rotation = glm::degrees(atan2f(m_Velocity.y, m_Velocity.x)) - 90.f;
    // m_Rotation = glm::radians(m_Velocity.y * 3.f);
    
    // Update Velocity
    if (b_IsUp)
    {
        m_Velocity.y += m_Acc;
        if (m_Velocity.y > 100.f)
        {
            b_IsUp = false; 
        }
    }
    else
    {
        m_Velocity.y -= m_Gravity;
    }
    m_Velocity = clamp(m_Velocity, -200.f, 200.f);

    m_AccumulateTime += ts;
    auto particleOffset = glm::vec2(0.f, -m_Scale.y / 2.f - Random::Rand(20.f, 30.f));
    auto rotMat = glm::mat2(1.f);
    auto const radRot = glm::radians(m_Rotation);
    rotMat[0][0] = cos(radRot);
    rotMat[0][1] = sin(radRot);
    rotMat[1][0] = -sin(radRot);
    rotMat[1][1] = cos(radRot);
    particleOffset = rotMat * particleOffset;
    if (m_AccumulateTime >= m_IntervalTime)
    {
        m_ParticleSystemComp->GetParticleProps().Position = m_Position + particleOffset;
        m_ParticleSystemComp->GetParticleProps().Rotation = m_Rotation;
        m_ParticleSystemComp->Emit();
        m_AccumulateTime = 0.f;
    }
    m_ParticleSystemComp->OnUpdate(ts);
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
