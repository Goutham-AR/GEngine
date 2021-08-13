#pragma once

#include <common.hh>
#include <events/Event.hh>

#include <string>
#include <string_view>
#include <functional>
#include <memory>

struct GLFWwindow;


namespace GE
{

    class GraphicsContext;

struct WindowProps final
{
    std::string title;
    unsigned int width;
    unsigned int height;

    explicit WindowProps(std::string_view title_ = "GEngine", unsigned int width_ = 1280, unsigned int height_ = 720)
        : title{title_},
          width{width_},
          height{height_}
    {
    }
};

class GE_PUBLIC Window
{
public:
    explicit Window(const WindowProps& props = WindowProps{});
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    [[nodiscard]] unsigned int getWidth() const { return m_winData.width; };
    [[nodiscard]] unsigned int getheight() const { return m_winData.height; };
    [[nodiscard]] GLFWwindow* getWinHandle() const { return m_window; }

    void onUpdate();

    using EventCallbackFn = std::function<void(Event&)>;
    void setEventCallback(const EventCallbackFn& callback);

    void setVSync(bool value);
    [[nodiscard]] bool isVSyncEnabled() const;

    static std::unique_ptr<Window> create(const WindowProps& props = WindowProps{});

private:
    void init();
    void shutdown();

    struct WinData
    {
        std::string title;
        unsigned int width;
        unsigned int height;
        bool vSync;
        EventCallbackFn eventCallback;
    };

private:
    WinData m_winData;
    GLFWwindow* m_window;
    GraphicsContext* m_context;
};

}