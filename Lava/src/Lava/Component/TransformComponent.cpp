#include "lvpch.h"
#include "TransformComponent.h"

#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    TransformComponent::TransformComponent(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
    {
        Position = pos;
        Rotation = rot;
        Scale = scale;

        auto constexpr Identity = glm::mat4(1.f);
        auto const transMat = translate(Identity, Position);
        auto const scaleMat = glm::scale(Identity, Scale);

        auto const rad = radians(Rotation);
        float const sx = sin(rad.x);
        float const sy = sin(rad.y);
        float const sz = sin(rad.z);
        float const cx = cos(rad.x);
        float const cy = cos(rad.y);
        float const cz = cos(rad.z);
        auto rotMatX = Identity;
        rotMatX[1][1] = cx;
        rotMatX[1][2] = -sx;
        rotMatX[2][1] = sx;
        rotMatX[2][2] = cx;
        auto rotMatY = Identity;
        rotMatY[0][0] = cy;
        rotMatY[0][2] = sy;
        rotMatY[2][0] = -sy;
        rotMatY[2][2] = cy;
        auto rotMatZ = Identity;
        rotMatZ[0][0] = cz;
        rotMatZ[0][1] = -sz;
        rotMatZ[1][0] = sz;
        rotMatZ[1][1] = cz;
        // auto const rotMatX = rotate(Identity, Rotation.x, glm::vec3(1.f, 0.f, 0.f));
        // auto const rotMatY = rotate(Identity, Rotation.y, glm::vec3(0.f, 1.f, 0.f));
        // auto const rotMatZ = rotate(Identity, Rotation.z, glm::vec3(0.f, 0.f, 1.f));
        TransformMatrix = transMat * rotMatX * rotMatY * rotMatZ * scaleMat;
    }

    glm::mat4 TransformComponent::GetTransMat()
    {
        auto constexpr Identity = glm::mat4(1.f);
        auto const transMat = translate(Identity, Position);
        auto const scaleMat = scale(Identity, Scale);

        auto const rad = radians(Rotation);
        float const sx = sin(rad.x);
        float const sy = sin(rad.y);
        float const sz = sin(rad.z);
        float const cx = cos(rad.x);
        float const cy = cos(rad.y);
        float const cz = cos(rad.z);
        auto rotMatX = Identity;
        rotMatX[1][1] = cx;
        rotMatX[1][2] = -sx;
        rotMatX[2][1] = sx;
        rotMatX[2][2] = cx;
        auto rotMatY = Identity;
        rotMatY[0][0] = cy;
        rotMatY[0][2] = sy;
        rotMatY[2][0] = -sy;
        rotMatY[2][2] = cy;
        auto rotMatZ = Identity;
        rotMatZ[0][0] = cz;
        rotMatZ[0][1] = -sz;
        rotMatZ[1][0] = sz;
        rotMatZ[1][1] = cz;
        // auto const rotMatX = rotate(Identity, Rotation.x, glm::vec3(1.f, 0.f, 0.f));
        // auto const rotMatY = rotate(Identity, Rotation.y, glm::vec3(0.f, 1.f, 0.f));
        // auto const rotMatZ = rotate(Identity, Rotation.z, glm::vec3(0.f, 0.f, 1.f));
        TransformMatrix = transMat * rotMatX * rotMatY * rotMatZ * scaleMat;
        return TransformMatrix;
    }

    glm::mat4 TransformComponent::GetRotMat() const
    {
        auto constexpr Identity = glm::mat4(1.f);

        float const sx = sin(Rotation.x);
        float const sy = sin(Rotation.y);
        float const sz = sin(Rotation.z);
        float const cx = cos(Rotation.x);
        float const cy = cos(Rotation.y);
        float const cz = cos(Rotation.z);
        auto rotMatX = Identity;
        rotMatX[1][1] = cx;
        rotMatX[1][2] = -sx;
        rotMatX[2][1] = sx;
        rotMatX[2][2] = cx;
        auto rotMatY = Identity;
        rotMatY[0][0] = cy;
        rotMatY[0][2] = sy;
        rotMatY[2][0] = -sy;
        rotMatY[2][2] = cy;
        auto rotMatZ = Identity;
        rotMatZ[0][0] = cz;
        rotMatZ[0][1] = -sz;
        rotMatZ[1][0] = sz;
        rotMatZ[1][1] = cz;
        // auto const rotMatX = rotate(Identity, Rotation.x, glm::vec3(1.f, 0.f, 0.f));
        // auto const rotMatY = rotate(Identity, Rotation.y, glm::vec3(0.f, 1.f, 0.f));
        // auto const rotMatZ = rotate(Identity, Rotation.z, glm::vec3(0.f, 0.f, 1.f));
        return rotMatZ * rotMatY * rotMatX;
    }
}
