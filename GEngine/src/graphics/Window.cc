#include "Window.hh"

#include <Logger.hh>

namespace GE
{

static bool isGLFWInitialized = false;

std::unique_ptr<Window> Window::create(const WindowProps& props)
{
    return std::make_unique<Window>(props);
}

Window::Window(const WindowProps& props)
    : m_winData{},
      m_window{}
{
    m_winData.title = props.title;
    m_winData.width = props.width;
    m_winData.height = props.height;

    init();
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}

void Window::init()
{
    ENGINE_LOG_INFO("Creating Window: {0}, {1}, {2}", m_winData.title, m_winData.width, m_winData.height);

    if (!isGLFWInitialized)
    {
        auto success = glfwInit();
        GE_ASSERT(success, "GLFW Initialization Failed");

        isGLFWInitialized = true;
    }

    ENGINE_LOG_INFO("Initialized GLFW");

    m_window = glfwCreateWindow(
        static_cast<int>(m_winData.width),
        static_cast<int>(m_winData.height),
        m_winData.title.c_str(),
        nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, &m_winData);

    setVSync(true);
}

void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void Window::setVSync(bool value)
{
    if (value)
    {
        glfwSwapInterval(1);
    }
    else
    {
        glfwSwapInterval(0);
    }

    m_winData.vSync = value;
}

bool Window::isVSyncEnabled() const
{
    return m_winData.vSync;
}

};