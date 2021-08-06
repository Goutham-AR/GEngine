#include "Window.hh"

#include <iostream>

namespace GE::core
{

void window_resize_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);

Window::Window(const WindowProps& props)
    : m_width{props.width},
      m_height{props.height},
      m_title{props.title},
      m_window{nullptr},
      m_closed{false},
      m_mouseX{},
      m_mouseY{},
      m_keys{},
      m_mouseButtons{}
{
    if (!init())
    {
        glfwTerminate();
    }

    for (bool& key : m_keys)
    {
        key = false;
    }

    for (bool& btn : m_mouseButtons)
    {
        btn = false;
    }
}

// Window class Related
// ---------------------
// static init

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::is_closed() const
{
    m_closed = static_cast<bool>(glfwWindowShouldClose(m_window));
    return m_closed;
}

void Window::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
    auto error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "ERROR:OPENGL:" << error << std::endl;  
    }
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

bool Window::init()
{
    if (glfwInit() != GLFW_TRUE)
    {
        std::cerr << "ERROR: Failed to initialize GLFW\n"
                  << "PLATFORM Error" << std::endl;
        return false;
    }
    std::cout << "GLFW Initialization: Success\n";

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        std::cerr << "ERROR: Failed to create the window" << std::endl;
        return false;
    }
    std::cout << "Window Creation: Success\n";

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetWindowSizeCallback(m_window, window_resize_callback);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetCursorPosCallback(m_window, cursor_pos_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "ERROR: Failed to initialize Glad" << std::endl;
        return false;
    }
    std::cout << "Glad Initialization: Success\n";

    return true;
} // Window::init()

bool Window::is_key_pressed(unsigned int keycode) const
{
    // TODO: Log this
    if (keycode > MAX_KEYS)
    {
        std::cerr << "ERROR: Invalid Keycode" << std::endl;
        return false;
    }

    return m_keys[keycode];
}

bool Window::is_mouse_btn_pressed(unsigned int btncode) const
{
    // TODO: Log this
    if (btncode > MAX_BUTTONS)
    {
        std::cerr << "ERROR: Invalid Keycode" << std::endl;
        return false;
    }

    return m_mouseButtons[btncode];
}

// ------------------
// Window class end

void window_resize_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->m_height = newHeight;
    win->m_width = newWidth;
    glViewport(0, 0, newWidth, newHeight);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->m_keys[key] = (action != GLFW_RELEASE);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->m_mouseButtons[button] = (action != GLFW_RELEASE);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    win->m_mouseX = xpos;
    win->m_mouseY = ypos;
}

} // namespace GE::core