﻿#pragma once

#include "Lava/Events/Event.h"

namespace Lava
{
    class ApplicationEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryApp)

        ApplicationEvent() = default;
    };

    class WindowCloseEvent: public ApplicationEvent
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
    
    class WindowFocusEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowFocus)

        WindowFocusEvent() = default;
    };
    
    class WindowLostFocusEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(WindowLostFocus)

        WindowLostFocusEvent() = default;
    };
    
    class WindowMovedEvent: public ApplicationEvent
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

    class AppTickEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(AppTick)

        AppTickEvent() = default;
    };

    class AppUpdateEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(AppUpdate)

        AppUpdateEvent() = default;
    };

    class AppRenderEvent: public ApplicationEvent
    {
    public:
        EVENT_CLASS_TYPE(AppRender)

        AppRenderEvent() = default;
    };
}
