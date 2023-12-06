#pragma once

#include "Lava/Events/Event.h"

#include <sstream>

#include "Lava.h"

namespace Lava
{
    class LAVA_API MouseMoveEvent: public Event
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

    class LAVA_API MouseScrolledEvent: public Event
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

    class LAVA_API MouseButtonEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

        unsigned int GetMouseButton() const { return m_ButtonCode; }

    protected:
        MouseButtonEvent(unsigned int button)
            : m_ButtonCode(button) {}
        unsigned int m_ButtonCode { 0 };
    };

    class LAVA_API MouseButtonPressedEvent: public MouseButtonEvent
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
        MouseButtonPressedEvent(unsigned int button)
            : MouseButtonEvent(button) {}
    };

    class LAVA_API MouseButtonReleasedEvent: public MouseButtonEvent
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
        MouseButtonReleasedEvent(unsigned int button)
            : MouseButtonEvent(button) {}
    };
}
