#include "lvpch.h"
#include "Camera.h"
#include "Lava/Core/Input.h"
#include "Lava/Core/KeyCodes.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Lava
{
    Camera::Camera(const CameraBox& param)
        : m_Box(param), m_ViewMatrix(1.f)
    {
        LV_PROFILE_FUNCTION();
        
        // m_Position = glm::vec3(0.f, 0.f, 0.f);
        // m_Rotation = glm::vec3(0.f, 0.f, 0.f);
        auto const width_2 = param.aspectRatio * param.height * param.zoomLevel / 2.f;
        auto const height_2 = param.height * param.zoomLevel / 2.f; 
        m_ProjMatrix = glm::ortho(-width_2, width_2, -height_2, height_2);
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }
    
    void Camera::SetViewMatrix(const glm::vec3& position, float rotation)
    {
        LV_PROFILE_FUNCTION();
        
        auto const dTrans = position - m_Position;
        m_Position = position;
        auto const dRot = rotation - m_Rotation.z;
        m_Rotation.z = rotation;
        
        auto constexpr Identity = glm::mat4(1.f);
        auto const RotMatrix = rotate(Identity, dRot, glm::vec3(0.f, 0.f, 1.f));
        auto const TransMatrix = translate(Identity, dTrans);

        m_ViewMatrix = inverse(RotMatrix * TransMatrix) * m_ViewMatrix;
        
        UpdateVPMatrix();
    }


    void Camera::SetProjMatrix(float aspectRatio, float zoomLevel)
    {
        LV_PROFILE_FUNCTION();
        
        m_Box.aspectRatio = aspectRatio;
        m_Box.zoomLevel = zoomLevel;
        auto const width_2 = m_Box.aspectRatio * m_Box.height * m_Box.zoomLevel / 2.f;
        auto const height_2 = m_Box.height * m_Box.zoomLevel / 2.f;
        
        m_ProjMatrix = glm::ortho(-width_2, width_2, -height_2, height_2);

        UpdateVPMatrix();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    glm::mat4 Camera::GetProjMatrix() const
    {
        return m_ProjMatrix;
    }

    glm::mat4 Camera::GetVPMatrix() const
    {
        return m_VPMatrix;
    }

    Ref<Camera> Camera::Create(const CameraBox& param)
    {
        return CreateRef<Camera>(param);
    }

    void Camera::UpdateVPMatrix()
    {
        LV_PROFILE_FUNCTION();
        
        m_VPMatrix = m_ProjMatrix * m_ViewMatrix;
    }

    CameraController::CameraController(const Ref<Camera>& camera, bool rotation)
        : m_Camera(camera)
        , m_Rotation(rotation)
    {
        LV_PROFILE_FUNCTION();
        
        m_CameraPosition = m_Camera->GetPosition();
        m_CameraRotation = m_Camera->GetRotation();
        m_CameraAspectRatio = m_Camera->GetCameraBox().aspectRatio;
        m_CameraZoomLevel = m_Camera->GetCameraBox().zoomLevel;
    }

    void CameraController::OnUpdate(Timestep ts)
    {
        LV_PROFILE_FUNCTION();
        
        if (Input::IsKeyPressed(LV_KEY_D))
            m_CameraPosition.x += m_CameraTransSpeed * ts;
        else if (Input::IsKeyPressed(LV_KEY_A))
            m_CameraPosition.x -= m_CameraTransSpeed * ts;
        else if (Input::IsKeyPressed(LV_KEY_W))
            m_CameraPosition.y += m_CameraTransSpeed * ts;
        else if (Input::IsKeyPressed(LV_KEY_S))
            m_CameraPosition.y -= m_CameraTransSpeed * ts;
        
        if (m_Rotation)
        {
            if (Input::IsKeyPressed(LV_KEY_Q))
                m_CameraRotation += m_CameraRotSpeed * ts;
            else if (Input::IsKeyPressed(LV_KEY_E))
                m_CameraRotation -= m_CameraRotSpeed * ts;
        }

        // m_Camera->SetPosition(m_CameraPosition);
        // m_Camera->SetRotation(m_CameraRotation);
        m_Camera->SetViewMatrix(m_CameraPosition, m_CameraRotation);
    }

    void CameraController::OnEvent(Event* e)
    {
        LV_PROFILE_FUNCTION();
        
        auto dispatcher = EventDispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_EVENT(CameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_EVENT(CameraController::OnWindowResized));
    }

    void CameraController::SetCamera(const Ref<Camera>& camera)
    {
        m_Camera = camera;
    }

    Ref<Camera> CameraController::GetCamera() const
    {
        return m_Camera;
    }

    bool CameraController::OnMouseScrolled(MouseScrolledEvent* e)
    {
        LV_PROFILE_FUNCTION();
        
        m_CameraZoomLevel -= e->GetOffsetY() * m_CameraZoomSpeed * 0.01f;
        if (m_CameraZoomLevel < 1e-6f)
        {
            m_CameraZoomLevel = 1e-6f;
        }
        else if (m_CameraZoomLevel > 100.f)
        {
            m_CameraZoomLevel = 100.f;
        }
        
        m_Camera->SetProjMatrix(m_CameraAspectRatio, m_CameraZoomLevel);
        return false;
    }

    bool CameraController::OnWindowResized(WindowResizeEvent* e)
    {
        LV_PROFILE_FUNCTION();
        
        m_WindowWidth = e->GetWidth();
        m_WindowHeight = e->GetHeight();
        
        m_CameraAspectRatio = static_cast<float>(e->GetWidth())
            / static_cast<float>(e->GetHeight());
        
        // LV_CORE_WARN("Windows Width: {0}, Height: {1}", e->GetWidth(), e->GetHeight());
        
        m_Camera->SetProjMatrix(m_CameraAspectRatio, m_CameraZoomLevel);
        return false;
    }
}
