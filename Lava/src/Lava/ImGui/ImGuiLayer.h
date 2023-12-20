#pragma once
#include "Lava/Layer.h"
#include "Lava/Events/ApplicationEvent.h"
#include "Lava/Events/KeyboardEvent.h"
#include "Lava/Events/MouseEvent.h"

namespace Lava
{
    class LAVA_API ImGuiLayer: public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event* e) override;

    private:
        void UpdateKeyModifiers(unsigned int mods) const;
        bool OnMouseMoveEvent(MouseMoveEvent* e);
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent* e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent* e);
        bool OnMouseScrolledEvent(MouseScrolledEvent* e);
        bool OnKeyPressedEvent(KeyPressedEvent* e);
        bool OnKeyReleasedEvent(KeyReleasedEvent* e);
        bool OnKeyTypedEvent(KeyTypedEvent* e);
        bool OnWindowResizedEvent(WindowResizeEvent* e);
        bool OnWindowCloseEvent(WindowCloseEvent* e);
    
    private:
        float m_Time { 0.f };
    };
}

