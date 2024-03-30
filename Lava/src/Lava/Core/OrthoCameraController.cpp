#include "lvpch.h"
#include "OrthoCameraController.h"

#include "Application.h"
#include "Input.h"
#include "KeyCodes.h"

namespace Lava
{
    OrthoCameraController::OrthoCameraController(const Ref<OrthoCamera>& camera, bool rotation)
        : m_Camera(camera)
        , m_Rotation(rotation)
    {
        LV_PROFILE_FUNCTION();

        auto props = m_Camera->GetInternalProps();
        auto const width = Application::Get()->GetWindow()->GetWidth();
        auto const height = Application::Get()->GetWindow()->GetHeight();
        
        props.AspectRatio = static_cast<float>(width)
            / static_cast<float>(height);
        
        m_Camera->UpdateInternalProps(props);
    }

    void OrthoCameraController::OnUpdate(Timestep ts)
    {
        LV_PROFILE_FUNCTION();

        auto props = m_Camera->GetExternalProps();
        if (Input::IsKeyPressed(LV_KEY_D))
            props.Position.x += m_CameraTransSpeed * ts;
        else if (Input::IsKeyPressed(LV_KEY_A))
            props.Position.x -= m_CameraTransSpeed * ts;
        else if (Input::IsKeyPressed(LV_KEY_W))
            props.Position.y += m_CameraTransSpeed * ts;
        else if (Input::IsKeyPressed(LV_KEY_S))
            props.Position.y -= m_CameraTransSpeed * ts;
        
        if (m_Rotation)
        {
            if (Input::IsKeyPressed(LV_KEY_Q))
                props.Roll += m_CameraRotSpeed * ts;
            else if (Input::IsKeyPressed(LV_KEY_E))
                props.Roll -= m_CameraRotSpeed * ts;
        }

        m_Camera->UpdateExternalProps(props);
    }

    void OrthoCameraController::OnEvent(Event* e)
    {
        LV_PROFILE_FUNCTION();
        
        auto dispatcher = EventDispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_CLASS_EVENT(OrthoCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_CLASS_EVENT(OrthoCameraController::OnWindowResized));
    }

    void OrthoCameraController::SetCamera(const Ref<OrthoCamera>& camera)
    {
        m_Camera = camera;
    }

    Ref<OrthoCamera> OrthoCameraController::GetCamera() const
    {
        return m_Camera;
    }

    bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent* e)
    {
        LV_PROFILE_FUNCTION();

        auto props = m_Camera->GetInternalProps();
        props.Height -= e->GetOffsetY() * m_CameraZoomSpeed;
        if (props.Height < 0.1f)
        {
            props.Height = 0.1f;
        }
        else if (props.Height > 10.f)
        {
            props.Height = 10.f;
        }
        
        m_Camera->UpdateInternalProps(props);
        return false;
    }

    bool OrthoCameraController::OnWindowResized(WindowResizeEvent* e)
    {
        LV_PROFILE_FUNCTION();

        auto props = m_Camera->GetInternalProps();
        auto const width = e->GetWidth();
        auto const height = e->GetHeight();
        
        props.AspectRatio = static_cast<float>(width)
            / static_cast<float>(height);
        
        m_Camera->UpdateInternalProps(props);
        return false;
    }
}
