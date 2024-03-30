#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    struct LAVA_API ScaleComponent
    {
        glm::vec3 Scale { 1.f };
        glm::mat4 ScaleMatrix { 1.f };

        ScaleComponent(const glm::vec3& scale): Scale(scale)
        {
            ScaleMatrix = glm::scale(glm::mat4(1.f), scale);
        }

        static std::string StaticType() { return "ScaleComponent"; }
    };
}
