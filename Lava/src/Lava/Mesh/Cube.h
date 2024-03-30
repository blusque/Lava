#pragma once
#include "Lava/Component/StaticMeshComponent.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Lava/Core/Entity.h"

namespace Lava
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexID;
    };
}
