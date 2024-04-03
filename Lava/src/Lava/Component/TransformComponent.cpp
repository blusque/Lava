#include "lvpch.h"
#include "TransformComponent.h"

#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    TransformComponent::TransformComponent(const glm::vec3& pos, const glm::vec3& rot)
    {
        Position = pos;
        Rotation = rot;

        auto constexpr Identity = glm::mat4(1.f);
        auto const transMat = translate(Identity, Position);
        auto rotMat = rotate(Identity, rot.x, glm::vec3(1.f, 0.f, 0.f));
        rotMat = rotate(rotMat, rot.y, glm::vec3(0.f, 1.f, 0.f));
        rotMat = rotate(rotMat, rot.z, glm::vec3(0.f, 0.f, 1.f));
        TransformMatrix = transMat * rotMat;
    }
}
