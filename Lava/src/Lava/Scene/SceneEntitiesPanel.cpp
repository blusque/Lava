#include "lvpch.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "SceneEntitesPanel.h"
#include "Lava/Component/CameraComponent.h"
#include "Lava/Component/MaterialComponent.h"
#include "Lava/Component/NameComponent.h"
#include "Lava/Component/RenderableComponent.h"
#include "Lava/Component/StaticMeshComponent.h"
#include "Lava/Component/TransformComponent.h"
#include "Lava/Core/Entity.h"

namespace Lava
{
    SceneEntitiesPanel::SceneEntitiesPanel(const Ref<Scene>& scene)
    {
        m_Scene = scene;
    }

    void SceneEntitiesPanel::OnGuiRender()
    {
        if (auto const scene = m_Scene.lock())
        {
            ImGui::Begin("Scene Entities Panel");

            scene->GetWorld()->view<NameComponent>().each([&](auto entityID, const NameComponent& name)
            {
                DrawEntityNode(entityID, name);
            });
            
            ImGui::End();

            ImGui::Begin("Properties");

            if (m_SelectedElem != entt::null)
            {
                DrawProperties(Entity::Create(m_SelectedElem, scene->GetWorld()));
            }
            
            ImGui::End();
        }
    }

    void SceneEntitiesPanel::DrawProperties(const Ref<Entity>& entity)
    {
        if (entity->HasComponent<NameComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(NameComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Name"))
            {
                auto& name = entity->GetComponent<NameComponent>().Name;
                char buffer[256] { 0 };
                memcpy_s(buffer, sizeof(buffer), name.data(), name.size());
            
                ImGui::Text("Name ");
                ImGui::SameLine();
                // ImGui::SetColumnOffset(1, 10.f);
                if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
                {
                    name = std::string(buffer);
                }

                ImGui::TreePop();
            }
        }

        if (entity->HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(TransformComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& position = entity->GetComponent<TransformComponent>().Position;
                auto& rotation = entity->GetComponent<TransformComponent>().Rotation;

                ImGui::DragFloat3("Position", value_ptr(position), 0.1f);

                ImGui::DragFloat3("Rotation", value_ptr(rotation), 0.1f);
                // ImGui::Text("Position");
                // ImGui::InputFloat("X ", &position.x);
                // ImGui::InputFloat("Y ", &position.y);
                // ImGui::InputFloat("Z ", &position.z);
                //
                // ImGui::Text("Rotation");
                // ImGui::InputFloat("X ", &rotation.x);
                // ImGui::InputFloat("Y ", &rotation.y);
                // ImGui::InputFloat("Z ", &rotation.z);

                ImGui::TreePop();
            }
        }

        if (entity->HasComponent<CameraComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(CameraComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
            {
                const auto& camera = entity->GetComponent<CameraComponent>();
                const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
                const char* currentProjectionType = projectionTypeStrings[camera.Camera->GetViewMethod()];

                if (ImGui::BeginCombo("Projection", currentProjectionType))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        bool const isSelected = currentProjectionType == projectionTypeStrings[i];
                        if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                        {
                            currentProjectionType = projectionTypeStrings[i];
                            camera.Camera->SetViewMethod(static_cast<Camera::View>(i));
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                if (camera.Camera->GetViewMethod() == Camera::View::Perspective)
                {
                    auto props = camera.Camera->GetPerspectiveIntrinsicProps();
                    ImGui::DragFloat("FOV", &props.FOV);
                    ImGui::DragFloat("Near Clip", &props.Near);
                    ImGui::DragFloat("Far Clip", &props.Far);
                    camera.Camera->UpdatePerspectiveIntrinsicProps(props);
                }
                else if (camera.Camera->GetViewMethod() == Camera::View::Orthogonal)
                {
                    auto props = camera.Camera->GetOrthogonalIntrinsicProps();
                    ImGui::DragFloat("Size", &props.Size);
                    ImGui::DragFloat("Near Clip", &props.Near);
                    ImGui::DragFloat("Far Clip", &props.Far);
                    camera.Camera->UpdateOrthogonalIntrinsicProps(props);
                }
                
                ImGui::TreePop();
            }
        }

        if (entity->HasComponent<RenderableComponent>())
        {
            
        }

        if (entity->HasComponent<StaticMeshComponent>())
        {
            
        }

        if (entity->HasComponent<MaterialComponent>())
        {
            
        }
    }

    void SceneEntitiesPanel::DrawEntityNode(const entt::entity& entityID, const NameComponent& name)
    {
        auto& Name = name.Name;
        auto const Flags = (m_SelectedElem == entityID ? ImGuiTreeNodeFlags_Selected : 0) |  ImGuiTreeNodeFlags_OpenOnArrow;
        bool const opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uint64_t>(static_cast<uint32_t>(entityID))), Flags, Name.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectedElem = entityID;
        }
        else if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            m_SelectedElem = entt::null;
        }
        if (opened)
        {
            ImGui::TreePop();
            ImGui::Text("\t%s", Name.c_str());
        }
        
    }
}
