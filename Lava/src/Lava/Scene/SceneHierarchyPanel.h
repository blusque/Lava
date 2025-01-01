#pragma once
#include "Scene.h"
#include "Lava/Component/TagComponent.h"

namespace Lava
{
    class LAVA_API SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(const Ref<Scene>& scene);
        ~SceneHierarchyPanel() = default;

        void OnGuiRender();

        void DrawProperties(const Ref<Entity>& entity);

    private:
        void DrawEntityNode(const entt::entity& entityID, const TagComponent& name);
        
        WeakRef<Scene> m_Scene;
        entt::entity m_SelectedElem { entt::null };
    };
     
}
