#pragma once

#include "Lava/Core.h"
#include "lvpch.h"

namespace Lava
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApp = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }
    
    class Event
    {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetEventCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) const
        {
            return GetEventCategoryFlags() & category;
        }

        bool Handled() const { return m_EventHandled; }
    protected:
        bool m_EventHandled { false };
    };
    using EventUPtr = std::unique_ptr<Event>;

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T*)>;
    public:
        EventDispatcher(Event* event)
            : m_Event(event) {}

        template<typename T>
        bool Dispatch(const EventFn<T>& func)
        {
            if (m_Event->GetEventType() == T::GetStaticType())
            {
                m_Event->m_EventHandled = func(static_cast<T*>(m_Event));
                return true;
            }
            return false;
        }

    protected:
        Event* m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}