#pragma once

#include <entt.hpp>
#include "Lava/Scene/Scene.h"

namespace Lava
{
    // namespace Mirror
    // {
    //     namespace detail
    //     {
    //         // auto entity = Entity;
    //         // entity.AddComponent<***Component>(entity.GetBasicEntity(), Args...);
    //         
    //         class Entity
    //         {
    //         public:
    //             Entity();
    //             ~Entity();
    //             
    //         private:
    //             template <typename... Args>
    //             class _BasicEntity
    //             {
    //             public:
    //                 static constexpr size_t TypeSize = sizeof...(Args);
    //
    //             public:
    //                 _BasicEntity() = default;
    //                 _BasicEntity(const entt::entity& other): m_Entity(other) {}
    //
    //                 auto GetEntityID() const { return m_Entity; }
    //
    //             private:
    //                 entt::entity m_Entity { entt::null };
    //             };
    //
    //         public:
    //             decltype(auto) GetBasicEntity() const
    //             {
    //                 return _BasicEntity<>();
    //             }
    //
    //         
    //             template <class Ty, typename... CompArgs, typename... EntityComps>
    //             decltype(auto) AddComponent(const _BasicEntity<EntityComps...>& entity, CompArgs&&... args)
    //             {
    //                 auto result = _BasicEntity<Ty, EntityComps...>(entity.GetEntityID());
    //                 if (auto const scene = m_Scene.lock())
    //                 {
    //                     scene->GetWorld()->emplace<Ty>(result.GetEntityID(), std::forward<CompArgs>(args...));
    //                 }
    //
    //                 return result;
    //             }
    //
    //             entt::entity m_Entity { entt::null };
    //             WeakRef<Scene> m_Scene;
    //         };
    //     }
    // }
    
    class LAVA_API Entity
    {
    public:
        Entity() = delete;
        Entity(entt::entity entityID, const Ref<entt::registry>& registry);
        Entity(const Ref<entt::registry>& registry);
        virtual ~Entity() = default;
        
        template <class Ty, typename... Args>
        void AddComponent(Args&&... args)
        {
            if (HasComponent<Ty>())
            {
                LV_CORE_WARN("Entity already has such component!");
            }
            else
            {
                if (auto const registry = m_Registry.lock())
                {
                    registry->emplace<Ty>(m_Entity, std::forward<Args>(args)...);
                }
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

        Ref<entt::registry> GetRegistryRef() const { return m_Registry.lock(); }

        operator bool() const { return m_Entity != entt::null; }
        operator uint32_t() const { return static_cast<uint32_t>(m_Entity); }
        operator entt::entity() const { return m_Entity; }
        
    private:
        entt::entity m_Entity { entt::null };
        WeakRef<entt::registry> m_Registry;
    };
}
