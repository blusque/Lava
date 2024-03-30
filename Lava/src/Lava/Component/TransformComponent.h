#pragma once
#include <glm/mat4x4.hpp>

namespace Lava
{
    struct LAVA_API TransformComponent
    {
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::mat4 TransformMatrix;

        TransformComponent(const glm::vec3& Position, const glm::vec3& Rotation);
        
        static std::string StaticType() { return "TransformComponent"; }
    };
}
