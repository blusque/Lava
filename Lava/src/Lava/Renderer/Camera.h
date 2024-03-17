#pragma once
#include <glm/glm.hpp>

#include "Lava/Events/ApplicationEvent.h"
#include "Lava/Events/MouseEvent.h"
#include "Lava/Core/Timestep.h"

namespace Lava
{
    struct CameraFOV
    {
        float FOV;
        float Aspect;
        float Far;
        float Near;
    };

    struct CameraBox
    {
        float height;
        float aspectRatio;
        float zoomLevel;
    };
    
    class LAVA_API Camera
    {
    public:
        Camera(const CameraBox& param);
        virtual ~Camera() {}

        void SetViewMatrix(const glm::vec3& position, float rotation);
        void SetProjMatrix(float aspectRatio, float zoom);

        [[nodiscard]] glm::vec3 GetPosition() const { return m_Position; }
        [[nodiscard]] float GetRotation() const { return m_Rotation.z; }
        [[nodiscard]] CameraBox GetCameraBox() const { return m_Box; }

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjMatrix() const;
        [[nodiscard]] glm::mat4 GetVPMatrix() const;
        
        static Ref<Camera> Create(const CameraBox& param);
        
    private:
        void UpdateVPMatrix();
        
    private:
        CameraBox m_Box;
        // glm::vec3 m_Rotation;   // axis-angle representation
        glm::vec3 m_Rotation { 0.f };
        glm::vec3 m_Position { 0.f };

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_VPMatrix;
    };

    class LAVA_API CameraController
    {
    public:
        CameraController() = default;
        CameraController(const Ref<Camera>& camera, bool rotation = false);
        ~CameraController() = default;

        void OnUpdate(Timestep ts);
        
        void OnEvent(Event* e);

        void SetCamera(const Ref<Camera>& camera);
        Ref<Camera> GetCamera() const;

        template <typename... Args>
        static Ref<CameraController> Create(Args&&... args)
        {
            return CreateRef<CameraController>(std::forward<Args>(args)...);
        }

        static Ref<CameraController> Create()
        {
            return CreateRef<CameraController>();
        }

        [[nodiscard]] unsigned GetWindowWidth() const { return m_WindowWidth; }
        [[nodiscard]] unsigned GetWindowHeight() const { return m_WindowHeight; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent* e);
        bool OnWindowResized(WindowResizeEvent* e);

    private:
        Ref<Camera> m_Camera { nullptr };
        
        bool m_Rotation { false };

        // Camera Related Info
        glm::vec3 m_CameraPosition { 0.f, 0.f, 0.f};
        float m_CameraRotation { 0.f };
        float m_CameraAspectRatio { 1920.f / 1080.f };
        float m_CameraZoomLevel { 1.f };
        float m_CameraTransSpeed { 5.f };
        float m_CameraRotSpeed { 1.57f };
        float m_CameraZoomSpeed { 1.f };

        unsigned m_WindowWidth { 1920 };
        unsigned m_WindowHeight { 1080 };
    };
}
