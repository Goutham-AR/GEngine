#pragma once
#define GLFW_INCLUDE_NONE

#include <string>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace GE::core
{

struct WindowProps
{
    int width{};
    int height{};
    std::string title{};

    WindowProps(int _width, int _height, std::string_view _name)
        : width{_width}, height{_height}, title{_name}
    {
    }

    WindowProps(const WindowProps&) = default;
    WindowProps& operator=(const WindowProps&) = default;

    ~WindowProps() = default;
};

class Window
{

    static constexpr std::size_t MAX_KEYS = 1024;
    static constexpr std::size_t MAX_BUTTONS = 32;

private:
    int m_width;
    int m_height;
    std::string m_title;
    GLFWwindow* m_window;
    mutable bool m_closed;

    bool m_keys[MAX_KEYS];
    bool m_mouseButtons[MAX_BUTTONS];
    double m_mouseX;
    double m_mouseY;

public:
    explicit Window(const WindowProps& props = WindowProps{1000, 800, "Window Title"});
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    [[nodiscard]] bool is_closed() const;
    void update();
    void clear() const;

    [[nodiscard]] inline int get_width() const { return m_width; }
    [[nodiscard]] inline int get_height() const { return m_height; }

    // INPUT related
    [[nodiscard]] bool is_key_pressed(unsigned int keycode) const;
    [[nodiscard]] bool is_mouse_btn_pressed(unsigned int btncode) const;
    [[nodiscard]] double get_mouse_y() const { return m_mouseY; }
    [[nodiscard]] double get_mouse_x() const { return m_mouseX; }

private:
    [[nodiscard]] bool init();

    // INPUT handlers for GLFW
    friend void window_resize_callback(GLFWwindow* window, int width, int height);
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    friend void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
};

} // namespace GE::core