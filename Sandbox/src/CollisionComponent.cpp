#include "CollisionComponent.h"

#include <glm/mat2x2.hpp>
#include <glm/trigonometric.hpp>

#include "Lava/Core.h"
#include "Lava/Core/Log.h"
#include "Lava/Renderer/Renderer2D.h"

CollisionComponent::CollisionComponent(PolygonType type, const std::vector<glm::vec2>& params)
{
    m_PolygonType = type;
    switch (type)
    {
    case PolygonType::Triangle:
        {
            LV_ASSERT(params.size() == 3, "params num error!")
            m_Params = params;
            CreateCollisionCompTriangle();
            break;
        }
    case PolygonType::Square:
        {
            LV_ASSERT(params.size() == 4, "params num error!")
            m_Params = params;
            CreateCollisionCompSquare();
            break;
        }
    default: break;
    }
}

void CollisionComponent::Show(const glm::vec2& globalPos, float globalRot) const
{
    auto rotMat = glm::mat2(1.f);
    auto const radRot = glm::radians(globalRot);
    rotMat[0][0] = cos(radRot);
    rotMat[0][1] = sin(radRot);
    rotMat[1][0] = -sin(radRot);
    rotMat[1][1] = cos(radRot);
    auto const center = m_Center + globalPos;
    Lava::Renderer2D::DrawRotateQuad(
        { center.x, center.y, 0.9f }, radRot,
        { 20.f, 20.f }, { 1.f, 0.f, 0.f, 1.f });
    for (auto param : m_Params)
    {
        param = rotMat * param;
        param += globalPos;
        Lava::Renderer2D::DrawRotateQuad(
            param, radRot, { 10.f, 10.f }, { 1.f, 0.f, 0.f, 1.f });
    }
    for (auto angle : m_ProjAngles)
    {
        angle += globalRot;
        auto const radAngle = glm::radians(angle);
        Lava::Renderer2D::DrawRotateQuad(
            { center.x, center.y, 0.9f }, radAngle,
            { 3.f, 50.f }, { 0.f, 0.f, 1.f, 1.f });
    }
}

void CollisionComponent::CreateCollisionCompTriangle()
{
    m_Center = glm::vec2(0.f);
    for (auto&& param : m_Params)
    {
        m_Center += param;
    }
    m_Center /= 3.f;
    for (auto&& param : m_Params)
    {
        m_Radius = std::max(m_Radius, distance(m_Center, param));
    }
    auto const side1 = m_Params[1] - m_Params[0];
    auto const side2 = m_Params[2] - m_Params[1];
    auto const side3 = m_Params[0] - m_Params[2];
    auto constexpr eps = 1e-6f;
    auto const angle1 = glm::degrees(atan2f(side1.x, -side1.y));
    auto const angle2 = glm::degrees(atan2f(side2.x, -side2.y));
    auto const angle3 = glm::degrees(atan2f(side3.x, -side3.y));
    m_ProjAngles.emplace_back(angle1);
    m_ProjAngles.emplace_back(angle2);
    m_ProjAngles.emplace_back(angle3);
}

void CollisionComponent::CreateCollisionCompSquare()
{
    m_Center = glm::vec2(0.f);
    for (auto&& param : m_Params)
    {
        m_Center += param;
    }
    m_Center /= 4.f;
    for (auto&& param : m_Params)
    {
        m_Radius = std::max(m_Radius, distance(m_Center, param));
    }
    m_ProjAngles.emplace_back(0.f);
    m_ProjAngles.emplace_back(90.f);
}

bool DetectCollision(const Lava::Ref<CollisionComponent>& comp1, const Lava::Ref<CollisionComponent>& comp2, const glm::vec2& pos1,
    float rot1, const glm::vec2& pos2, float rot2)
{
    LV_ASSERT(comp1->GetPolygonType() == CollisionComponent::PolygonType::Square
        && comp2->GetPolygonType() == CollisionComponent::PolygonType::Triangle, "Now only support that~!")
    auto const dist = distance(comp1->GetCenter() + pos1, comp2->GetCenter() + pos2);
    if (dist > comp1->GetRadius() + comp2->GetRadius())
    {
        return false;
    }
    
    float projAngle[10] = { 0.f };
    memcpy(projAngle, comp1->GetProjAngles().data(), 2);
    auto index = 2;
    for (auto&& angle : comp2->GetProjAngles())
    {
        bool sameFlag = false;
        for (int i = 0; i < 2; i++)
        {
            if (abs(angle - projAngle[i]) < 5.f)
            {
                sameFlag = true;
                break;
            }
        }
        if (!sameFlag)
        {
            projAngle[index] = angle;
            index++;
        }
    }

    auto vec = glm::vec2(0.f);
    for (int i = 0; i < index; i++)
    {
        if (i < 2)
        {
            vec.x = cos(glm::radians(projAngle[i] + rot1));
            vec.y = sin(glm::radians(projAngle[i] + rot1));
        }
        else
        {
            vec.x = cos(glm::radians(projAngle[i] + rot2));
            vec.y = sin(glm::radians(projAngle[i] + rot2));
        }
        
        auto comp1Max = -1e32f, comp1Min = 1e32f;
        for (auto point : comp1->GetParams())
        {
            point += pos1;
            auto const x = dot(vec, point);
            comp1Max = std::max(comp1Max, x);
            comp1Min = std::min(comp1Min, x);
        }

        auto comp2Max = -1e32f, comp2Min = 1e32f;
        for (auto point : comp2->GetParams())
        {
            point += pos2;
            auto const x = dot(vec, point);
            comp2Max = std::max(comp2Max, x);
            comp2Min = std::min(comp2Min, x);
        }

        if (comp1Max < comp2Min || comp1Min > comp2Max)
        {
            return false;
        }
    }
    return true;
}
