#include "lvpch.h"
#include "Entity.h"

namespace Lava
{
    Entity::Entity(entt::entity entityID, const Ref<entt::registry>& registry)
    {
        m_Registry = registry;
        m_Entity = entityID;
    }

    Entity::Entity(const Ref<entt::registry>& registry)
    {
        m_Registry = registry;
        if (auto const reg = m_Registry.lock())
        {
            m_Entity = reg->create();
        }
    }
}

