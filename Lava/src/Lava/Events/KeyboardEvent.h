#pragma once

#include "Lava/Events/Event.h"

namespace Lava
{
    class KeyboardEvent: public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
        
        unsigned int GetMods() const { return m_Mods; }
        
        unsigned int GetKey() const { return m_KeyCode; }
    protected:
        KeyboardEvent(unsigned int key, unsigned int mods)
            : m_KeyCode(key), m_Mods(mods) {}
        unsigned int m_KeyCode;
        unsigned int m_Mods { 0 };
    };

    class KeyPressedEvent: public KeyboardEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyPressed)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Key (" << m_KeyCode << ") pressed " << m_RepeatNum << " times, Mods: " << m_Mods << "!";
            return ss.str();
        }

    public:
        KeyPressedEvent(unsigned int key, unsigned int repeat, unsigned int mods)
            : KeyboardEvent(key, mods), m_RepeatNum(repeat) {}
        
    private:
        unsigned int m_RepeatNum { 0 };
    };

    class KeyReleasedEvent: public KeyboardEvent
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
        KeyReleasedEvent(unsigned int key, unsigned int mods)
            : KeyboardEvent(key, mods) {}
    };

    class KeyTypedEvent: public KeyboardEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyTyped)

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "Key (" << m_KeyCode << ") typed ";
            return ss.str();
        }

    public:
        KeyTypedEvent(unsigned int key)
            : KeyboardEvent(key, 0) {}
    };
}
