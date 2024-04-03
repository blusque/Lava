#pragma once
#include "Lava/Material/Material.h"

namespace Lava
{
    struct LAVA_API MaterialComponent
    {
        Ref<PhongMaterial> MaterialInstance;

        MaterialComponent(const Ref<PhongMaterial>& material);
    };
}
