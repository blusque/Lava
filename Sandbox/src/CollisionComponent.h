#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "Lava/Core.h"

class CollisionComponent
{
public:
    enum class PolygonType
    {
        Triangle,
        Square
    };

    CollisionComponent(PolygonType type, const std::vector<glm::vec2>& params);

    void Show(const glm::vec2& globalPos, float globalRot) const;

    PolygonType GetPolygonType() const { return m_PolygonType; }
    auto GetCenter() const { return m_Center; }
    auto GetParams() const { return m_Params; }
    auto GetRadius() const { return m_Radius; }
    auto GetProjAngles() const { return m_ProjAngles; }
    
private:
    void CreateCollisionCompTriangle();
    
    void CreateCollisionCompSquare();
    
private:
    PolygonType m_PolygonType;
    std::vector<glm::vec2> m_Params;
    glm::vec2 m_Center;
    std::vector<float> m_ProjAngles;
    float m_Radius;
    
};

bool DetectCollision(const Lava::Ref<CollisionComponent>& comp1, const Lava::Ref<CollisionComponent>& comp2,
    const glm::vec2& pos1, float rot1, const glm::vec2& pos2, float rot2);
