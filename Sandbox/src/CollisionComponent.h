#pragma once
#include <vector>
#include <glm/vec2.hpp>

class CollisionComponent
{
public:
    enum class PolygonType
    {
        Triangle,
        Square
    };

    CollisionComponent(PolygonType type, const std::vector<glm::vec2>& params);

    void Show(const glm::vec2& globalPos, float globalRot);
    
private:
    void CreateCollisionCompTriangle();
    
    void CreateCollisionCompSquare();
    
private:
    PolygonType m_PolygonType;
    std::vector<glm::vec2> m_Params;
    glm::vec2 m_Center;
    std::vector<float> m_ProjAngles;
    float m_MaxDist;
    
};

bool DetectCollision(const CollisionComponent& comp1, const CollisionComponent& comp2,
    const glm::vec2& pos1, float rot1, const glm::vec2& pos2, float rot2);
