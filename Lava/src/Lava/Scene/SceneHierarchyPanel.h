﻿#pragma once
#include "Scene.h"
#include "Lava/Core/Entity.h"
#include "Lava/Component/TagComponent.h"

namespace Lava
{
    void DrawDragVec3(const char* label, glm::vec3& value, float resetValue = 0.0f, float columnWidth = 150.0f,
        float step=0.1f, float min=0.f, float max=0.f);
    
    class LAVA_API SceneHierarchyPanel
    {
        using DrawCompFunc = std::function<void(const Ref<Entity>&)>; // std::function<void(const Ref<Entity>&)>;
    public:
        SceneHierarchyPanel(const Ref<Scene>& scene);
        ~SceneHierarchyPanel() = default;

        void OnGuiRender();

        void DrawProperties(const Ref<Entity>& entity);

        template <typename T>
        static void DrawComponent(const Ref<Entity>& entity, const char* name, const DrawCompFunc& drawFunc)
        {
            if (entity->HasComponent<T>())
            {
                if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(T).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, name))
                {
                    drawFunc(entity);
                    ImGui::TreePop();
                }
            }
        }

    private:
        void DrawEntityNode(const entt::entity& entityID, const TagComponent& name);
        
        WeakRef<Scene> m_Scene;
        entt::entity m_SelectedElem { entt::null };
    };
     
}
