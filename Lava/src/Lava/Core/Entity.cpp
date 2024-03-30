#include "lvpch.h"
#include "Entity.h"

namespace Lava
{
    Entity::Entity()
    {
        m_Entity = m_Registry.create();
    }

    Ref<Entity> Entity::Create()
    {
        return CreateRef<Entity>();
    }
}

