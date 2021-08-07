#pragma once

#include "Event.hh"

#include <sstream>

namespace GE
{

class GE_PUBLIC MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_x{x},
          m_y{y}
    {
    }

    [[nodiscard]] inline float getX() const { return m_x; }
    [[nodiscard]] inline float getY() const { return m_y; }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "MouseMovedEvent: (" << m_x << ", " << m_y << ")";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::MouseMoved; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(MouseMoved); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_Mouse | EC_Input; }

private:
    float m_x;
    float m_y;
};

class GE_PUBLIC MouseButtonEvent : public Event
{
public:
    [[nodiscard]] inline int getMouseButton() const { return m_button; }

    [[nodiscard]] int getCategoryFlags() const override { return EC_Mouse | EC_Input; }

protected:
    explicit MouseButtonEvent(int button)
        : m_button{button}
    {
    }

    int m_button;
};

class GE_PUBLIC MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    explicit MouseButtonPressedEvent(int button)
        : MouseButtonEvent{button}
    {
    }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "MouseButtonPressedEvent: " << m_button;
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::MouseButtonPressed; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(MouseButtonPressed); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_Mouse | EC_Input; }
};

class GE_PUBLIC MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    explicit MouseButtonReleasedEvent(int button)
        : MouseButtonEvent{button}
    {
    }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "MouseButtonReleasedEvent: " << m_button;
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::MouseButtonReleased; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(MouseButtonReleased); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_Mouse | EC_Input; }
};

class GE_PUBLIC MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_xOffset{xOffset},
          m_yOffset{yOffset}
    {
    }

    [[nodiscard]] inline float getXOffset() const { return m_xOffset; }
    [[nodiscard]] inline float getYOffset() const { return m_yOffset; }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "MouseScrolledEvent: (" << m_xOffset << ", " << m_yOffset << ")";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::MouseScrolled; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(MouseScrolled); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_Mouse | EC_Input; }

private:
    float m_xOffset;
    float m_yOffset;
};

}