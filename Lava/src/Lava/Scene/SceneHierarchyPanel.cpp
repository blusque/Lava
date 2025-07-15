#include "lvpch.h"

#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "SceneHierarchyPanel.h"

#include "imgui_internal.h"
#include "Lava/Component/CameraComponent.h"
#include "Lava/Component/MaterialComponent.h"
#include "Lava/Component/TagComponent.h"
#include "Lava/Component/RenderableComponent.h"
#include "Lava/Component/StaticMeshComponent.h"
#include "Lava/Component/TransformComponent.h"

namespace Lava
{
    void DrawDragVec3(const char* label, glm::vec3& value, float resetValue, float columnWidth,
            float step, float min, float max)
    {
        ImGui::PushID(label);
        
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label);
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.25f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.0f, 0.05f, 1.0f));
        if (ImGui::Button("X", buttonSize))
        {
            value.x = resetValue;
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##X", &value.x, 0.1f, 0.f, 0.f, "%.3f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.8f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.9f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.7f, 0.1f, 1.0f));
        if (ImGui::Button("Y", buttonSize))
        {
            value.y = resetValue;
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &value.y, 0.1f, 0.f, 0.f, "%.3f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.85f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.95f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.75f, 1.0f));
        if (ImGui::Button("Z", buttonSize))
        {
            value.z = resetValue;
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &value.z, 0.1f, 0.f, 0.f, "%.3f");
        ImGui::PopItemWidth();
        
        ImGui::Columns(1);
        ImGui::PopStyleVar();
        ImGui::PopID();
    }
    
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
    {
        m_Scene = scene;
    }

    void SceneHierarchyPanel::OnGuiRender()
    {
        if (auto const scene = m_Scene.lock())
        {
            ImGui::Begin("Hierarchy");
            scene->GetWorld()->view<TagComponent>().each([&](auto entityID, auto& tag)
            {
                auto entity = Entity{ entityID, scene->GetWorld() };
                DrawEntityNode(entity);
            });
            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            {
                m_SelectedEntity = Entity{ entt::null, nullptr };
            }
            if (ImGui::BeginPopupContextWindow("Create Entity", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                {
                    scene->AddEntity("Empty Entity");
                }
                ImGui::EndPopup();
            }
            ImGui::End();

            ImGui::Begin("Inspector");
            if (m_SelectedEntity)
            {
                DrawProperties(m_SelectedEntity);
            }
            ImGui::End();
        }
    }

    void SceneHierarchyPanel::DrawProperties(Entity& entity)
    {
        DrawComponent<TagComponent>(entity, "Tag", [&](Entity& e)
        {
            auto& tag = e.GetComponent<TagComponent>().Tag;
            char buffer[256] { 0 };
            memcpy_s(buffer, sizeof(buffer), tag.data(), tag.size());
            
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
            ImGui::SameLine();
            ImGui::Text("Tag");
        });

        DrawComponent<TransformComponent>(entity, "Transform", [&](Entity& e)
        {
            auto& position = e.GetComponent<TransformComponent>().Position;
            auto& rotation = e.GetComponent<TransformComponent>().Rotation;
            auto& scale = e.GetComponent<TransformComponent>().Scale;

            DrawDragVec3("Position", position);
            DrawDragVec3("Rotation", rotation);
            DrawDragVec3("Scale", scale, 1.f);
        });

        DrawComponent<CameraComponent>(entity, "Camera", [&](Entity& e)
        {
            auto& camera = e.GetComponent<CameraComponent>();
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
        });

        DrawComponent<StaticMeshComponent>(entity, "Static Mesh", [&](Entity& e)
        {
        });

        DrawComponent<MaterialComponent>(entity, "Material", [&](Entity& e)
        {
        });

        if (entity.HasComponent<RenderableComponent>())
        {
            
        }
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& Name = entity.GetComponent<TagComponent>().Tag;
        auto const Flags = (m_SelectedEntity == static_cast<entt::entity>(entity) ? ImGuiTreeNodeFlags_Selected : 0) |  ImGuiTreeNodeFlags_OpenOnArrow;
        bool const opened = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uint64_t>(static_cast<uint32_t>(entity))),
            Flags, Name.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectedEntity = Entity{ entity, entity.GetRegistryRef() };
        }

        bool EntityDeleted = false;
        if (ImGui::BeginPopupContextItem(nullptr, ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::MenuItem("Delete Entity"))
            {
                EntityDeleted = true;
            }
            ImGui::EndPopup();
        }
        
        if (opened)
        {
            // if (ImGui::TreeNodeEx(reinterpret_cast<void*>(12032), ImGuiTreeNodeFlags_OpenOnArrow,
            //     Name.c_str()))
            // {
            //     ImGui::TreePop();
            // }
            ImGui::Text(Name.c_str());
            ImGui::TreePop();
        }

        if (EntityDeleted)
        {
            if (auto const scene = m_Scene.lock())
            {
                scene->DestroyEntity(entity);
                if (m_SelectedEntity == static_cast<entt::entity>(entity))
                {
                    m_SelectedEntity = Entity{ entt::null, nullptr };
                }
            }
        }
    }
}

