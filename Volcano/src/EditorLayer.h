#pragma once

#include <Lava.h>

#include "Lava/Scene/SceneHierarchyPanel.h"

#define ASSETS_ROOT "C:/Users/kokut/dev/Lava/Valcano/assets/"
#define ASSETS_FILE(x) LV_STR(x)
#define ASSETS_PATH(x) LV_CONCAT(ASSETS_ROOT, ASSETS_FILE(x))

namespace Lava
{
    class EditorLayer: public Layer
    {
    public:
        EditorLayer()
            : Layer("EditorLayer Layer")
            , m_SceneCamera(Camera::Create({
                { -1.f, 0.f, 5.f },
                { 0.2f, 0.f, -1.f },
                { 0.f, 1.f, 0.f }
            }))
            , m_SceneCameraController(CameraController::Create(m_SceneCamera))
        {
        }
        ~EditorLayer() override = default;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(Timestep ts) override;

        void OnEvent(Event* e) override;

        void OnGuiRender() override;

    private:
        bool OnWindowResized(WindowResizeEvent* e);

        void ShowExampleMenuItems();

        void StartGame();

    private:
        Ref<Texture> m_Texture;

        Ref<Camera> m_SceneCamera;
        Ref<CameraController> m_SceneCameraController;
        
        WeakRef<Camera> m_PrimaryCamera;

        Ref<Framebuffer> m_Framebuffer;
        Ref<Framebuffer> m_PostProcessingBuffer;
        Ref<Framebuffer> m_ShadowBuffer;

        Ref<Scene> m_MainScene;
        Ref<SceneHierarchyPanel> m_SceneHierarchyPanel;
        Ref<ShaderLibrary> m_ShaderLibrary;
        glm::vec2 m_FramebufferSize { 0.f };
        bool m_ViewportFocused { true };

        uint32_t m_WindowWidth { 0 };
        uint32_t m_WindowHeight { 0 };

        glm::vec4 m_SquColor { 0.2f, 0.3f, 0.8f, 1.f };

        float m_AccumulateTime { 0.f };
    };
    
}
