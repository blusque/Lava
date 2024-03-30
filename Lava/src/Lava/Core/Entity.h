#pragma once

#include <entt.hpp>
#include "Lava/Scene/Scene.h"

namespace Lava
{
    class LAVA_API Entity
    {
    public:
        Entity();
        virtual ~Entity() = default;
        
        template <class Ty, typename... Args>
        void AddComponent(Args&&... args)
        {
            LV_CORE_ASSERT(!HasComponent<Ty>(), "Entity already has such component!")
            m_Registry.emplace<Ty>(m_Entity, std::forward<Args>(args)...);
        }
        
        template <class Ty>
        bool HasComponent() const { return m_Registry.try_get<Ty>(m_Entity); }
        
        template <class Ty>
        Ty& GetComponent()
        {
            LV_CORE_ASSERT(HasComponent<Ty>(), "Entity does not have such component!")
            return m_Registry.get<Ty>(m_Entity);
        }

        operator bool() const { return m_Entity != entt::null; }
        
        static Ref<Entity> Create();
    private:
        entt::entity m_Entity { entt::null };
        entt::registry m_Registry;
    };
}
