#pragma once
#include <glm/mat4x4.hpp>

namespace Lava
{
    struct LAVA_API TransformComponent
    {
        glm::vec3 Position { 0.f, 0.f, 0.f };
        glm::vec3 Rotation { 0.f, 0.f, 0.f };
        glm::vec3 Scale {1.f, 1.f, 1.f};

        TransformComponent() = default;
        TransformComponent(const glm::vec3& Position, const glm::vec3& Rotation, const glm::vec3& Scale);
        
        static std::string StaticType() { return "TransformComponent"; }

        glm::mat4 GetTransMat() const;
        glm::mat4 GetRotMat() const;
    };
}
