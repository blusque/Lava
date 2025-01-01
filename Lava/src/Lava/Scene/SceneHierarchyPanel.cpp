#include "lvpch.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "SceneHierarchyPanel.h"
#include "Lava/Component/CameraComponent.h"
#include "Lava/Component/MaterialComponent.h"
#include "Lava/Component/TagComponent.h"
#include "Lava/Component/RenderableComponent.h"
#include "Lava/Component/StaticMeshComponent.h"
#include "Lava/Component/TransformComponent.h"
#include "Lava/Core/Entity.h"

namespace Lava
{
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
    {
        m_Scene = scene;
    }

    void SceneHierarchyPanel::OnGuiRender()
    {
        if (auto const scene = m_Scene.lock())
        {
            ImGui::Begin("Hierarchy");

            scene->GetWorld()->view<TagComponent>().each([&](auto entityID, const TagComponent& name)
            {
                DrawEntityNode(entityID, name);
            });
            
            ImGui::End();

            ImGui::Begin("Inspector");

            if (m_SelectedElem != entt::null)
            {
                DrawProperties(Entity::Create(m_SelectedElem, scene->GetWorld()));
            }
            
            ImGui::End();
        }
    }

    void SceneHierarchyPanel::DrawProperties(const Ref<Entity>& entity)
    {
        if (entity->HasComponent<TagComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(TagComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Tag"))
            {
                auto& tag = entity->GetComponent<TagComponent>().Tag;
                char buffer[256] { 0 };
                memcpy_s(buffer, sizeof(buffer), tag.data(), tag.size());
            
                ImGui::Text("Tag ");
                ImGui::SameLine();
                // ImGui::SetColumnOffset(1, 10.f);
                if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
                {
                    tag = std::string(buffer);
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
                auto& scale = entity->GetComponent<TransformComponent>().Scale;

                ImGui::DragFloat3("Position", value_ptr(position), 0.1f);
                ImGui::DragFloat3("Rotation", value_ptr(rotation), 0.1f);
                ImGui::DragFloat3("Scale", value_ptr(scale), 0.1f);
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
                const char* currentProjectionType = projectionTypeStrings[camera.Camera->GetPerspectiveType()];

                if (ImGui::BeginCombo("Projection", currentProjectionType))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        bool const isSelected = currentProjectionType == projectionTypeStrings[i];
                        if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                        {
                            currentProjectionType = projectionTypeStrings[i];
                            camera.Camera->SetPerspectiveType(static_cast<Camera::PerspectiveType>(i));
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                if (camera.Camera->GetPerspectiveType() == Camera::PerspectiveType::Perspective)
                {
                    auto props = camera.Camera->GetPerspectiveIntrinsicProps();
                    ImGui::DragFloat("FOV", &props.FOV);
                    ImGui::DragFloat("Near Clip", &props.Near);
                    ImGui::DragFloat("Far Clip", &props.Far);
                    camera.Camera->UpdatePerspectiveIntrinsicProps(props);
                }
                else if (camera.Camera->GetPerspectiveType() == Camera::PerspectiveType::Orthogonal)
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

    void SceneHierarchyPanel::DrawEntityNode(const entt::entity& entityID, const TagComponent& name)
    {
        auto& Name = name.Tag;
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
