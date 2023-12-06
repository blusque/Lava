#pragma once

#include "Lava/Events/Event.h"

#include <sstream>

namespace Lava
{
    class LAVA_API KeyboardEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

        unsigned int GetButton() const { return m_KeyCode; }
    protected:
        KeyboardEvent(unsigned int key)
            : m_KeyCode(key) {}
        unsigned int m_KeyCode;
    };

    class LAVA_API KeyPressedEvent: public KeyboardEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyPressed)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Key (" << m_KeyCode << ") pressed " << m_RepeatNum << " times!";
            return ss.str();
        }

    public:
        KeyPressedEvent(unsigned int key, unsigned int repeat)
            : KeyboardEvent(key), m_RepeatNum(repeat) {}
        
    private:
        unsigned int m_RepeatNum { 0 };
    };

    class LAVA_API KeyReleasedEvent: public KeyboardEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyReleased)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Key (" << m_KeyCode << ") released!";
            return ss.str();
        }

    public:
        KeyReleasedEvent(unsigned int key)
            : KeyboardEvent(key) {}
    };
}
