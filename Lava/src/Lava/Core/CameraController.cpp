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
        auto props = m_Camera->GetInternalProps();
        auto const width = Application::Get()->GetWindow()->GetWidth();
        auto const height = Application::Get()->GetWindow()->GetHeight();
        
        props.AspectRatio = static_cast<float>(width)
            / static_cast<float>(height);
        m_Camera->UpdateInternalProps(props);

        auto const external = m_Camera->GetExternalProps();
        m_CameraPosition = external.Position;
        m_CameraRotation.x = glm::degrees(atan2f(external.Orient.z, external.Orient.x));
        m_CameraRotation.y = glm::degrees(asinf(external.Orient.y));
        m_CameraRotation.y = glm::clamp(m_CameraRotation.y, -89.9f, 89.9f);
    }

    void CameraController::OnUpdate(float ts)
    {
        auto externalProps = m_Camera->GetExternalProps();
        auto const orient = externalProps.Orient;
        auto const right = glm::normalize(glm::cross(orient, externalProps.Up));
        if (Input::IsKeyPressed(LV_KEY_W))
        {
            externalProps.Position += ts * m_CameraSpeed * orient;
        }
        else if (Input::IsKeyPressed(LV_KEY_S))
        {
            externalProps.Position -= ts * m_CameraSpeed * orient;
        }
        else if (Input::IsKeyPressed(LV_KEY_D))
        {
            externalProps.Position += ts * m_CameraSpeed * right;
        }
        else if (Input::IsKeyPressed(LV_KEY_A))
        {
            externalProps.Position -= ts * m_CameraSpeed * right;
        }

        m_Camera->UpdateExternalProps(externalProps);
        m_CameraPosition = externalProps.Position;
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
        auto internalProps = m_Camera->GetInternalProps();

        internalProps.FOV -= e->GetOffsetY() * m_ZoomSpeed;
        internalProps.FOV = glm::clamp(internalProps.FOV, 1.f, 45.f);

        m_Camera->UpdateInternalProps(internalProps);

        return true;
    }

    bool CameraController::OnMouseMove(MouseMoveEvent* e)
    {
        auto const xPos = e->GetNewX();
        auto const yPos = e->GetNewY();
        // LV_CORE_TRACE("CursorPos Diff: {0}, {1}", xPos - m_LastCursorPos.x, m_LastCursorPos.y - yPos);
        if (Input::IsMouseButtonPressed(LV_MOUSE_BUTTON_1))
        {
            auto externalProps = m_Camera->GetExternalProps();
            m_CameraRotation.x += m_CursorSensitive * (xPos - m_LastCursorPos.x);
            m_CameraRotation.y += m_CursorSensitive * (m_LastCursorPos.y - yPos);
            m_CameraRotation.y = glm::clamp(m_CameraRotation.y, -89.9f, 89.9f);
        
            auto const pitch = glm::radians(m_CameraRotation.y);
            auto const yaw = glm::radians(m_CameraRotation.x);
            externalProps.Orient.x = cos(yaw) * cos(pitch);
            externalProps.Orient.y = sin(pitch);
            externalProps.Orient.z = sin(yaw) * cos(pitch);
            externalProps.Orient = normalize(externalProps.Orient);
            
            m_Camera->UpdateExternalProps(externalProps);
        }
        m_LastCursorPos.x = xPos;
        m_LastCursorPos.y = yPos;

        return false;
    }

    bool CameraController::OnWindowResized(WindowResizeEvent* e)
    {
        auto props = m_Camera->GetInternalProps();

        auto const width = e->GetWidth();
        auto const height = e->GetHeight();
        props.AspectRatio = static_cast<float>(width) /
            static_cast<float>(height);

        m_Camera->UpdateInternalProps(props);
        return false;
    }
}
