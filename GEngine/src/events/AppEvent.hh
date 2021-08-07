#pragma once

#include "Event.hh"

#include <sstream>

namespace GE
{
class GE_PUBLIC WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_width{width},
          m_height{height}
    {
    }

    [[nodiscard]] inline auto getWidth() const { return m_width; }
    [[nodiscard]] inline auto getHeight() const { return m_height; }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "WindowResizeEvent: " << m_width << ", " << m_height;
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::WindowResize; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(WindowResize); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_App; }

private:
    unsigned int m_width;
    unsigned int m_height;
};

class GE_PUBLIC WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "WindowCloseEvent: ";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::WindowClose; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(WindowClose); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_App; }
};

class GE_PUBLIC AppTickEvent : public Event
{
public:
    AppTickEvent() = default;

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "AppTickEvent: ";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::AppTick; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(AppTick); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_App; }
};

class GE_PUBLIC AppUpdateEvent : public Event
{
public:
    AppUpdateEvent() = default;

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "AppUpdateEvent: ";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::AppUpdate; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(AppUpdate); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_App; }
};

class GE_PUBLIC AppRenderEvent : public Event
{
public:
    AppRenderEvent() = default;

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "AppRenderEvent: ";
        return sstream.str();
    }
    static EventType getStaticType() { return EventType::AppRender; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(AppRender); }

    [[nodiscard]] int getCategoryFlags() const override { return EC_App; }
};
}