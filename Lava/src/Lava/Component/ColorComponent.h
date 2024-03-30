#pragma once
#include <glm/vec4.hpp>

namespace Lava
{
    struct LAVA_API ColorComponent
    {
        glm::vec4 Color { 1.f };

        ColorComponent(const glm::vec4& color) : Color(color) {}
    };

    static std::string StaticType() { return "ColorComponent"; }
}
