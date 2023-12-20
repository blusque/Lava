#pragma once

#include "Lava/Events/Event.h"

namespace Lava
{
    class MouseMoveEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
        EVENT_CLASS_TYPE(MouseMoved)

        float GetNewX() const { return m_X; }
        float GetNewY() const { return m_Y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Mouse moved to X: " << m_X << ", Y: " << m_Y;
            return ss.str();
        }

    public:
        MouseMoveEvent(float x, float y)
            : m_X(x), m_Y(y) {}
        
    private:
        float m_X { 0.f };
        float m_Y { 0.f };
    };

    class MouseScrolledEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
        EVENT_CLASS_TYPE(MouseScrolled)

        float GetOffsetX() const { return m_OffsetX; }
        float GetOffsetY() const { return m_OffsetY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Scrolled Offset X: " << m_OffsetX << ", Offset Y: " << m_OffsetY;
            return ss.str();
        }
        
    public:
        MouseScrolledEvent(float x, float y)
            : m_OffsetX(x), m_OffsetY(y) {}

    protected:
        float m_OffsetX { 0.f };
        float m_OffsetY { 0.f };
    };

    class MouseButtonEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

        unsigned int GetMods() const { return m_Mods; }
        
        unsigned int GetMouseButton() const { return m_ButtonCode; }

    protected:
        MouseButtonEvent(unsigned int button, unsigned int mods)
            : m_ButtonCode(button), m_Mods(mods) {}
        
        unsigned int m_ButtonCode { 0 };
        unsigned int m_Mods { 0 };
    };

    class MouseButtonPressedEvent: public MouseButtonEvent
    {
    public:
        EVENT_CLASS_TYPE(MouseButtonPressed)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Mouse button (" << m_ButtonCode << ") pressed!";
            return ss.str();
        }

    public:
        MouseButtonPressedEvent(unsigned int button, unsigned int mods)
            : MouseButtonEvent(button, mods) {}
    };

    class MouseButtonReleasedEvent: public MouseButtonEvent
    {
    public:
        EVENT_CLASS_TYPE(MouseButtonPressed)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Mouse button (" << m_ButtonCode << ") released!";
            return ss.str();
        }

    public:
        MouseButtonReleasedEvent(unsigned int button, unsigned int mods)
            : MouseButtonEvent(button, mods) {}
    };
}
