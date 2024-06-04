#pragma once
#include "Lava/Renderer/Camera.h"

namespace Lava
{
    class LAVA_API CameraController
    {
    public:
        CameraController(const Ref<Camera>& camera);
        ~CameraController() = default;

        void OnUpdate(float ts);
        void OnEvent(Event* e);
    
        Ref<Camera> GetCamera() const { return m_Camera; }
        glm::vec3 GetCameraPosition() const { return m_CameraPosition; }
        glm::vec3 GetCameraRotation() const { return m_CameraRotation; }
        bool IsActive() const { return m_Active; }
        
        void SetViewMethod(Camera::View viewMethod) const { m_Camera->SetViewMethod(viewMethod); }
        void Active(bool active) { m_Active = active; }

        static Ref<CameraController> Create(const Ref<Camera>& camera);

    private:
        bool OnMouseScrolled(MouseScrolledEvent* e);
        bool OnMouseMove(MouseMoveEvent* e);
        bool OnWindowResized(WindowResizeEvent* e);
    private:
        Ref<Camera> m_Camera;
        bool m_Active;
        float m_CameraSpeed { 5.f };
        glm::vec3 m_CameraPosition { 0.f };
        glm::vec3 m_CameraRotation { 0.f };
        glm::vec2 m_LastCursorPos { 0.f };
        float m_CursorSensitive { 0.05f };
        float m_ZoomSpeed { 0.5f };
    };
}
