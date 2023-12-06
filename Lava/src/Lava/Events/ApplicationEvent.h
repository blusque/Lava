#pragma once

#include <intrin.h>

#include "Lava/Events/Event.h"

#include <sstream>

namespace Lava
{
    class ApplicationEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryApp)

        ApplicationEvent() = default;
    };

    class LAVA_API WindowCloseEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowClose)

        WindowCloseEvent() = default;
    };
    
    class WindowResizeEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowResize)

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Window is resized to X: " << m_Width
                << ", Y: " << m_Height;
            return ss.str();
        }

    public:
        WindowResizeEvent(unsigned int x, unsigned int y)
            : m_Width(x), m_Height(y) {}

    protected:
        unsigned int m_Width { 0 };
        unsigned int m_Height { 0 };
    };
    
    class LAVA_API WindowFocusEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowFocus)

        WindowFocusEvent() = default;
    };
    
    class LAVA_API WindowLostFocusEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowLostFocus)

        WindowLostFocusEvent() = default;
    };
    
    class LAVA_API WindowMovedEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowMoved)

        unsigned int GetNewX() const { return m_X; }
        unsigned int GetNewY() const { return m_Y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Window is moved to X: " << m_X << ", Y: " << m_Y;
            return ss.str();
        }

    public:
        WindowMovedEvent(unsigned int x, unsigned int y)
            : m_X(x), m_Y(y) {}

    protected:
        unsigned int m_X { 0 };
        unsigned int m_Y { 0 };
    };

    class LAVA_API AppTickEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(AppTick)

        AppTickEvent() = default;
    };

    class LAVA_API AppUpdateEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(AppUpdate)

        AppUpdateEvent() = default;
    };

    class LAVA_API AppRenderEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(AppRender)

        AppRenderEvent() = default;
    };
}
