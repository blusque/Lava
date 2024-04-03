#pragma once

#include <entt.hpp>
#include "Lava/Scene/Scene.h"

namespace Lava
{
    class LAVA_API Entity
    {
    public:
        Entity() = delete;
        Entity(const Ref<entt::registry>& registry);
        virtual ~Entity() = default;
        
        template <class Ty, typename... Args>
        void AddComponent(Args&&... args)
        {
            LV_CORE_ASSERT(!HasComponent<Ty>(), "Entity already has such component!")
            if (auto const registry = m_Registry.lock())
            {
                registry->emplace<Ty>(m_Entity, std::forward<Args>(args)...);
            }
        }
        
        template <typename... Args>
        bool HasComponent() const
        {
            if (auto const registry = m_Registry.lock())
            {
                return registry->all_of<Args...>(m_Entity);
            }
            return false;
        }
        
        template <class Ty>
        Ty& GetComponent()
        {
            auto const registry = m_Registry.lock();
            LV_CORE_ASSERT(registry, "m_Registry may have been deleted!")
            LV_CORE_ASSERT(HasComponent<Ty>(), "Entity does not have such component!")
            return registry->get<Ty>(m_Entity);
        }

        operator bool() const { return m_Entity != entt::null; }
        
        static Ref<Entity> Create(const Ref<entt::registry>& registry);
    private:
        entt::entity m_Entity { entt::null };
        WeakRef<entt::registry> m_Registry;
    };
}
