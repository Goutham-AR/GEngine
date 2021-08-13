#include "Window.hh"

#include "events/AppEvent.hh"
#include "events/KeyEvent.hh"
#include "events/MouseEvent.hh"

#include <Logger.hh>
#include <graphics/GraphicsContext.hh>
#include <graphics/GL/GLContext.hh>

#include <GLFW/glfw3.h>

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
    shutdown();
}

void Window::init()
{
    ENGINE_LOG_INFO("Creating Window: {0}, {1}, {2}", m_winData.title, m_winData.width, m_winData.height);

    if (!isGLFWInitialized)
    {
        auto success = glfwInit();
        GE_ASSERT(success, "GLFW Initialization Failed");

        glfwSetErrorCallback(
            [](int error, const char* description)
            {
                ENGINE_LOG_ERROR("GLFW Error: Error code -> {0}, {1}", error, description);
            });
        isGLFWInitialized = true;
    }
    ENGINE_LOG_INFO("GLFW Initialization: Success");

    m_window = glfwCreateWindow(
        static_cast<int>(m_winData.width),
        static_cast<int>(m_winData.height),
        m_winData.title.c_str(),
        nullptr, nullptr);

    m_context = new GLContext{m_window};
    m_context->init();

    glfwSetWindowUserPointer(m_window, &m_winData);
    setVSync(true);

    glfwSetWindowSizeCallback(
        m_window,
        [](GLFWwindow* window, int newWidth, int newHeight)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));
            winData->width = newWidth;
            winData->height = newHeight;
            WindowResizeEvent event{
                static_cast<unsigned int>(newWidth),
                static_cast<unsigned int>(newHeight)};

            winData->eventCallback(event);
        });

    glfwSetWindowCloseCallback(
        m_window,
        [](GLFWwindow* window)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            winData->eventCallback(event);
        });

    glfwSetKeyCallback(
        m_window,
        [](GLFWwindow* window, int key, int scancode, int action, int mod)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event{toKeyCode(key), 0};
                winData->eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event{toKeyCode(key), 1};
                winData->eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event{toKeyCode(key)};
                winData->eventCallback(event);
                break;
            }
            default:
                break;
            }
        }); // glfwSetKeyCallback

    glfwSetCharCallback(
        m_window,
        [](GLFWwindow* window, unsigned int codePoint)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event{toKeyCode(static_cast<int>(codePoint))};

            winData->eventCallback(event);
        });

    glfwSetMouseButtonCallback(
        m_window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event{toMouseKey(button)};
                winData->eventCallback(event);
                break;
            }

            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event{toMouseKey(button)};
                winData->eventCallback(event);
                break;
            }

            default:
                break;
            }
        });

    glfwSetCursorPosCallback(
        m_window,
        [](GLFWwindow* window, double newXPos, double newYPos)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event{
                static_cast<float>(newXPos),
                static_cast<float>(newYPos)};

            winData->eventCallback(event);
        });

    glfwSetScrollCallback(
        m_window,
        [](GLFWwindow* window, double xOffset, double yOffset)
        {
            auto* winData = static_cast<WinData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event{
                static_cast<float>(xOffset),
                static_cast<float>(yOffset)};

            winData->eventCallback(event);
        });
}   // Window::init()

void Window::setEventCallback(const EventCallbackFn& callback)
{
    m_winData.eventCallback = callback;
}

void Window::onUpdate()
{
    glfwPollEvents();
    m_context->swapBuffers();
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

void Window::shutdown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

};