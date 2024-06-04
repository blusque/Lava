#pragma once
#include <entt.hpp>

#include "Lava/Component/LightSourceComponent.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "Lava/Renderer/Framebuffer.h"

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
        Scene();

        Ref<Entity> AddEntity(const std::string& name, glm::vec3 initPos = { 0.f, 0.f, 0.f },
            glm::vec3 initRot = { 0.f, 0.f, 0.f });

        Ref<Entity> AddLightSource(const std::string& name, LightSourceComponent::Kind kind,
            glm::vec3 initPos = { 0.f, 0.f, 0.f }, glm::vec3 initRot = { 0.f, 0.f, 0.f });

        Ref<entt::registry> GetWorld() const;

        void GetPrimaryCamera(WeakRef<Camera>& primaryCamera, const Ref<Camera>& sceneCamera) const;

        void UpdateCameraTrans() const;

        decltype(auto) GetLightSources() const
        {
            return m_World->view<LightSourceComponent>();
        }

        Ref<Entity> GetEntity(const std::string& name) const
        {
            return m_Entities.at(name);
        }

        void OnRender(const Ref<Camera>& camera, const Ref<Framebuffer>& shadowMap, const glm::mat4& shadowMat) const;

        void OnRenderer2D() const;
        
    private:
        Ref<entt::registry> m_World;
        std::unordered_map<std::string, Ref<Entity>> m_Entities;
    };
}
