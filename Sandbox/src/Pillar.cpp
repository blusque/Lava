﻿#include "Pillar.h"

#include "imgui.h"

Pillar::Pillar(glm::vec3 upPosition, glm::vec3 downPosition)
{
    // m_Index = index;
    // auto posUp = glm::vec3(0.f);
    // auto posDown = glm::vec3(0.f);
    // posUp.z = m_DeepZ * static_cast<float>(index);
    // posDown.z = m_DeepZ * static_cast<float>(index) + m_DeepZ / 2.f;
    //
    // posUp.x = m_DistX * static_cast<float>(index);
    // posDown.x = m_DistX * static_cast<float>(index);
    //
    // posUp.y = m_PosY;
    // posDown.y = -m_PosY;
    // m_Position.first = posUp;
    // m_Position.second = posDown;
    m_Position.first = upPosition;
    m_Position.second = downPosition;

    m_Texture = Lava::Texture::Create("C:/Users/kokut/dev/Lava/Sandbox/assets/textures/Triangle.png");
    auto const downCollidePoints = std::vector<glm::vec2>{
            { -250.f, -250.f },
            {  250.f, -250.f },
            {  2.f, 250.f }
    };
    auto const upCollidePoints = std::vector<glm::vec2>{
                { -250.f, 250.f },
                {  250.f, 250.f },
                {  -1.f, -250.f }
    };
    m_CollisionComp.first = Lava::CreateRef<CollisionComponent>(CollisionComponent::PolygonType::Triangle, upCollidePoints);
    m_CollisionComp.second = Lava::CreateRef<CollisionComponent>(CollisionComponent::PolygonType::Triangle, downCollidePoints);
}

void Pillar::OnBegin()
{
}

void Pillar::OnUpdate(Lava::Timestep ts)
{
}

void Pillar::OnGuiRender()
{
}

void Pillar::OnEvent(Lava::Event* e)
{
}
