﻿#include "lvpch.h"
#include "Scene.h"

#include "Lava/Component/CameraComponent.h"
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
    Scene::Scene()
    {
        m_World = CreateRef<entt::registry>();
    }

    Ref<Entity> Scene::AddEntity(const std::string& name, glm::vec3 initPos, glm::vec3 initRot)
    {
        auto entity = Entity::Create(m_World);
        m_Entities[name] = entity;
        entity->AddComponent<NameComponent>(name);
        entity->AddComponent<TransformComponent>(initPos, initRot);
        return entity;
    }

    Ref<Entity> Scene::AddLightSource(const std::string& name, LightSourceComponent::Kind kind, glm::vec3 initPos,
            glm::vec3 initRot)
    {
        auto entity = AddEntity(name, initPos, initRot);
        entity->AddComponent<LightSourceComponent>(kind);
        return entity;
    }

    Ref<entt::registry> Scene::GetWorld() const
    {
        return m_World;
    }

    void Scene::GetPrimaryCamera(WeakRef<Camera>& primaryCamera, const Ref<Camera>& sceneCamera) const
    {
        auto const cameras = m_World->view<CameraComponent>();
        bool getActive = false;

        for (auto&& [entity, camera] : cameras.each())
        {
            if (camera.IsActive)
            {
                primaryCamera = camera.Camera;
                getActive = true;
            }
        }

        if (!getActive)
        {
            primaryCamera = sceneCamera;
        }
    }

    void Scene::UpdateCameraTrans() const
    {
        m_World->view<TransformComponent, CameraComponent>().each(
            [] (auto e, auto& trans, auto& cam)
            {
                cam.UpdateExtrinsicProps(trans);
            });
    }

    void Scene::OnRender(const Ref<Camera>& camera, const Ref<Framebuffer>& shadowMap, const glm::mat4& shadowMat) const
    {
        auto const meshes = m_World->view<StaticMeshComponent, MaterialComponent,
            TransformComponent, ScaleComponent, RenderableComponent>(entt::exclude<LightSourceComponent>);
        auto const lights = m_World->view<TransformComponent, ColorComponent, LightSourceComponent>();
        Renderer::BeginScene(camera);
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
            material.MaterialInstance->SetEyePosition(camera->GetExtrinsicProps().Position);
            auto const transMat = trans.GetTransMat() * scale.ScaleMatrix;
            Renderer::Shadow(material.MaterialInstance->GetShader(), shadowMap, shadowMat);
            Renderer::Submit(mesh.VAO, material.MaterialInstance->GetShader(), transMat);
        }
        Renderer::EndScene();
    }

    void Scene::OnRenderer2D() const
    {
    }
}
