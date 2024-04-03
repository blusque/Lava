#include "lvpch.h"
#include "MaterialComponent.h"

namespace Lava
{
    MaterialComponent::MaterialComponent(const Ref<PhongMaterial>& material)
    {
        MaterialInstance = material;
    }
}
