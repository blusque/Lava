#include "lvpch.h"
#include "Entity.h"

namespace Lava
{
    Entity::Entity(const Ref<entt::registry>& registry)
    {
        m_Registry = registry;
        if (auto const reg = m_Registry.lock())
        {
            m_Entity = reg->create();
        }
    }

    Ref<Entity> Entity::Create(const Ref<entt::registry>& registry)
    {
        return CreateRef<Entity>(registry);
    }
}

