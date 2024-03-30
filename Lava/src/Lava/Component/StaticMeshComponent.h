#pragma once
#include "Lava/Renderer/VertexArray.h"

namespace Lava
{
    struct LAVA_API StaticMeshComponent
    {
        Ref<VertexArray> VAO;

        StaticMeshComponent(const void* data, uint32_t dataSize,
            const uint32_t* indices, uint32_t indicesSize);
        static std::string StaticType() { return "StaticMeshComponent"; }
    };
}
