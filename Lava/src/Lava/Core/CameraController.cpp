#include "lvpch.h"
#include "CameraController.h"

#include "Application.h"
#include "MouseButtonCodes.h"
#include "Lava/Core/Input.h"
#include "Lava/Core/KeyCodes.h"

namespace Lava
{
    CameraController::CameraController(const Ref<Camera>& camera)
        : m_Camera(camera)
    {
        auto const width = Application::Get()->GetWindow()->GetWidth();
        auto const height = Application::Get()->GetWindow()->GetHeight();
        
        m_Camera->UpdateAspectRatio(static_cast<float>(width) / static_cast<float>(height));

        auto const external = m_Camera->GetExtrinsicProps();
        m_CameraPosition = external.Position;
        m_CameraRotation.x = glm::degrees(atan2f(external.Orient.z, external.Orient.x));
        m_CameraRotation.y = glm::degrees(asinf(external.Orient.y));
        m_CameraRotation.y = glm::clamp(m_CameraRotation.y, -89.9f, 89.9f);
    }

    void CameraController::OnUpdate(float ts)
    {
        auto extrinsicProps = m_Camera->GetExtrinsicProps();
        auto const orient = extrinsicProps.Orient;
        auto const right = glm::normalize(glm::cross(orient, extrinsicProps.Up));
        if (Input::IsKeyPressed(LV_KEY_W))
        {
            extrinsicProps.Position += ts * m_CameraSpeed * orient;
        }
        else if (Input::IsKeyPressed(LV_KEY_S))
        {
            extrinsicProps.Position -= ts * m_CameraSpeed * orient;
        }
        else if (Input::IsKeyPressed(LV_KEY_D))
        {
            extrinsicProps.Position += ts * m_CameraSpeed * right;
        }
        else if (Input::IsKeyPressed(LV_KEY_A))
        {
            extrinsicProps.Position -= ts * m_CameraSpeed * right;
        }

        m_Camera->UpdateExtrinsicProps(extrinsicProps);
        m_CameraPosition = extrinsicProps.Position;
    }

    void CameraController::OnEvent(Event* e)
    {
        auto dispatcher = EventDispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&CameraController::OnMouseScrolled, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseMoveEvent>(std::bind(&CameraController::OnMouseMove, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CameraController::OnWindowResized, this, std::placeholders::_1));
    }

    Ref<CameraController> CameraController::Create(const Ref<Camera>& camera)
    {
        return CreateRef<CameraController>(camera);
    }

    bool CameraController::OnMouseScrolled(MouseScrolledEvent* e)
    {
        if (m_Camera->GetViewMethod() == Camera::Perspective)
        {
            auto props = m_Camera->GetPerspectiveIntrinsicProps();

            props.FOV -= e->GetOffsetY() * m_ZoomSpeed;
            props.FOV = glm::clamp(props.FOV, 1.f, 90.f);

            m_Camera->UpdatePerspectiveIntrinsicProps(props);
        }
        else if (m_Camera->GetViewMethod() == Camera::Orthogonal)
        {
            auto props = m_Camera->GetOrthogonalIntrinsicProps();

            props.Size -= e->GetOffsetY() * m_ZoomSpeed;
            props.Size = glm::clamp(props.Size, 1.f, 250.f);

            m_Camera->UpdateOrthogonalIntrinsicProps(props);
        }
        return true;
    }

    bool CameraController::OnMouseMove(MouseMoveEvent* e)
    {
        auto const xPos = e->GetNewX();
        auto const yPos = e->GetNewY();
        if (glm::abs(xPos - m_LastCursorPos.x) > 100.f || glm::abs(yPos - m_LastCursorPos.y) > 100.f)
        {
            m_LastCursorPos.x = xPos;
            m_LastCursorPos.y = yPos;
        }
        // LV_CORE_TRACE("CursorPos Diff: {0}, {1}", xPos - m_LastCursorPos.x, m_LastCursorPos.y - yPos);
        if (Input::IsMouseButtonPressed(LV_MOUSE_BUTTON_1))
        {
            auto extrinsicProps = m_Camera->GetExtrinsicProps();
            m_CameraRotation.x += m_CursorSensitive * (xPos - m_LastCursorPos.x);
            m_CameraRotation.y += m_CursorSensitive * (m_LastCursorPos.y - yPos);
            m_CameraRotation.y = glm::clamp(m_CameraRotation.y, -89.9f, 89.9f);
        
            auto const pitch = glm::radians(m_CameraRotation.y);
            auto const yaw = glm::radians(m_CameraRotation.x);
            extrinsicProps.Orient.x = cos(yaw) * cos(pitch);
            extrinsicProps.Orient.y = sin(pitch);
            extrinsicProps.Orient.z = sin(yaw) * cos(pitch);
            extrinsicProps.Orient = normalize(extrinsicProps.Orient);
            
            m_Camera->UpdateExtrinsicProps(extrinsicProps);
        }
        m_LastCursorPos.x = xPos;
        m_LastCursorPos.y = yPos;

        return false;
    }

    bool CameraController::OnWindowResized(WindowResizeEvent* e)
    {
        auto const width = Application::Get()->GetWindow()->GetWidth();
        auto const height = Application::Get()->GetWindow()->GetHeight();

        m_Camera->UpdateAspectRatio(static_cast<float>(width) / static_cast<float>(height));
        return false;
    }
}
