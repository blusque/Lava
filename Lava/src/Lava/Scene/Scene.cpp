#include "lvpch.h"
#include "Scene.h"

#include "Lava/Component/ColorComponent.h"
#include "Lava/Component/MaterialComponent.h"
#include "Lava/Component/NameComponent.h"
#include "Lava/Component/RenderableComponent.h"
#include "Lava/Component/ScaleComponent.h"
#include "Lava/Component/StaticMeshComponent.h"
#include "Lava/Component/TransformComponent.h"
#include "Lava/Core/Entity.h"
#include "Lava/Renderer/Renderer.h"

namespace Lava
{
    Scene::Scene(const Ref<Camera>& camera)
    {
        m_Camera = camera;
        m_World = CreateRef<entt::registry>();
    }

    Ref<Entity> Scene::AddEntity(const std::string& name)
    {
        auto entity = Entity::Create(m_World);
        m_Entities[name] = entity;
        return entity;
    }

    Ref<Entity> Scene::AddLightSource(const std::string& name, LightSourceComponent::Kind kind)
    {
        auto entity = AddEntity(name);
        entity->AddComponent<LightSourceComponent>(kind);
        return entity;
    }

    Ref<entt::registry> Scene::GetWorld() const
    {
        return m_World;
    }

    void Scene::OnRender() const
    {
        auto const meshes = m_World->view<StaticMeshComponent, MaterialComponent,
            TransformComponent, ScaleComponent, RenderableComponent>(entt::exclude<LightSourceComponent>);
        auto const lights = m_World->view<TransformComponent, ColorComponent, LightSourceComponent>();
        Renderer::BeginScene(m_Camera);
        for (auto&& [entity, mesh, material, trans, scale] : meshes.each())
        {
            for (auto&& [light, lightTrans, lightColor, kind] : lights.each())
            {
                if (kind.Which == LightSourceComponent::Kind::Parallel)
                {
                    auto const direction = lightTrans.Rotation;
                    auto const color = lightColor.Color;
                    material.MaterialInstance->SetParallelLight(direction, glm::vec3(color));
                }
                else if (kind.Which == LightSourceComponent::Kind::Point)
                {
                    auto const position = lightTrans.Position;
                    auto const color = lightColor.Color;
                    material.MaterialInstance->SetPointLight(position, glm::vec3(color));
                }
                else if (kind.Which == LightSourceComponent::Kind::Spot)
                {
                    auto const position = lightTrans.Position;
                    auto const direction = lightTrans.Rotation;
                    auto const color = lightColor.Color;
                    material.MaterialInstance->SetSpotLight(position, direction, glm::vec3(color));
                }
            }
            material.MaterialInstance->Bind();
            material.MaterialInstance->SetEyePosition(m_Camera->GetExternalProps().Position);
            auto const transMat = trans.TransformMatrix * scale.ScaleMatrix;
            Renderer::Submit(mesh.VAO, material.MaterialInstance->GetShader(), transMat);
        }
        Renderer::EndScene();
    }

    void Scene::OnRenderer2D() const
    {
    }
}
