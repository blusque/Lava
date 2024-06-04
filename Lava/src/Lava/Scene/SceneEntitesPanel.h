#pragma once
#include "Scene.h"
#include "Lava/Component/NameComponent.h"

namespace Lava
{
    class LAVA_API SceneEntitiesPanel
    {
    public:
        SceneEntitiesPanel(const Ref<Scene>& scene);
        ~SceneEntitiesPanel() = default;

        void OnGuiRender();

        void DrawProperties(const Ref<Entity>& entity);

    private:
        void DrawEntityNode(const entt::entity& entityID, const NameComponent& name);
        
        WeakRef<Scene> m_Scene;
        entt::entity m_SelectedElem { entt::null };
    };
     
}
