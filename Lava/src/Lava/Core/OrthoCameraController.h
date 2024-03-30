#pragma once
#include "Timestep.h"
#include "Lava/Events/ApplicationEvent.h"
#include "Lava/Events/Event.h"
#include "Lava/Events/MouseEvent.h"
#include "Lava/Renderer/OrthoCamera.h"

namespace Lava
{
    class LAVA_API OrthoCameraController
    {
    public:
        OrthoCameraController(const Ref<OrthoCamera>& camera, bool rotation = false);
        ~OrthoCameraController() = default;

        void OnUpdate(Timestep ts);
        
        void OnEvent(Event* e);

        void SetCamera(const Ref<OrthoCamera>& camera);
        Ref<OrthoCamera> GetCamera() const;

        static Ref<OrthoCameraController> Create(const Ref<OrthoCamera>& camera, bool rotation = false)
        {
            return CreateRef<OrthoCameraController>(camera, rotation);
        }

    private:
        bool OnMouseScrolled(MouseScrolledEvent* e);
        bool OnWindowResized(WindowResizeEvent* e);

    private:
        Ref<OrthoCamera> m_Camera { nullptr };
        
        bool m_Rotation { false };

        // Camera Related Info
        float m_CameraTransSpeed { 50.f };
        float m_CameraRotSpeed { 1.57f };
        float m_CameraZoomSpeed { 0.01f };
    };
}
