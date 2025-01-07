#pragma once

#include "assimp/Importer.hpp"

namespace Lava
{
    class LAVA_API StaticMeshLoader
    {
    public:
        static void LoadStaticMesh(const std::string& filePath);
    };       
}
