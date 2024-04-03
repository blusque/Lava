#pragma once
#include <entt.hpp>

#include "Lava/Component/LightSourceComponent.h"
#include <glm/vec3.hpp>

namespace Lava
{
    struct LightSourceComponent;
}

namespace Lava
{
    class Camera;
    class Entity;
    
    class LAVA_API Scene
    {
    public:
        Scene(const Ref<Camera>& camera);

        Ref<Entity> AddEntity(const std::string& name);

        Ref<Entity> AddLightSource(const std::string& name, LightSourceComponent::Kind kind);

        Ref<entt::registry> GetWorld() const;

        decltype(auto) GetLightSources() const
        {
            return m_World->view<LightSourceComponent>();
        }

        Ref<Entity> GetEntity(const std::string& name) const
        {
            return m_Entities.at(name);
        }

        void OnRender() const;

        void OnRenderer2D() const;
        
    private:
        Ref<Camera> m_Camera;
        Ref<entt::registry> m_World;
        std::unordered_map<std::string, Ref<Entity>> m_Entities;
    };
}
