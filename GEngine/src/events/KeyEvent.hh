#pragma once

#include "Event.hh"

#include <sstream>

namespace GE
{

class GE_PUBLIC KeyEvent : public Event
{

public:
    [[nodiscard]] int getCategoryFlags() const override { return EC_KeyBoard | EC_Input; }
    [[nodiscard]] int getKeyCode() const { return m_keyCode; }

protected:
    explicit KeyEvent(int keyCode)
        : m_keyCode{keyCode}
    {
    }

    int m_keyCode;
};

class GE_PUBLIC KeyPressedEvent : public KeyEvent
{
public:
    explicit KeyPressedEvent(int keyCode, int count)
        : KeyEvent{keyCode},
          m_count{count}
    {
    }

    [[nodiscard]] int getCount() const { return m_count; }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "KeyPressedEvent: " << m_keyCode << " (" << m_count << " repeats)";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::KeyPressed; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(KeyPressed); }

private:
    int m_count;
};

class GE_PUBLIC KeyReleasedEvent : public KeyEvent
{
public:
    explicit KeyReleasedEvent(int keyCode)
        : KeyEvent{keyCode}
    {
    }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "KeyReleasedEvent: " << m_keyCode;
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::KeyReleased; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(KeyReleased); }
};

class GE_PUBLIC KeyTypedEvent : public KeyEvent
{
public:
    explicit KeyTypedEvent(int keyCode)
        : KeyEvent{keyCode}
    {
    }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "KeyTypedEvent: " << m_keyCode;
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::KeyTyped; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(KeyTyped); }
};

}