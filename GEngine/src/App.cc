#include "App.hh"

#include <array>

#include <utils/Logger.hh>
#include <window/Input.hh>
#include <window/KeyCode.hh>
#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>
#include <Time.hh>
#include <graphics/Renderer.hh>

namespace GE
{
// singleton
App* App::appInstance = nullptr;

App::App()
    : m_imGuiLayer{nullptr},
      m_layerStack{}
{
    GE_ASSERT(!appInstance, "Only one App can exist");
    appInstance = this;

    m_window = Window::create();
    m_window->setEventCallback(
        [this](Event& e)
        {
            EventDispatcher dispatcher{e};

            dispatcher.dispatchEvent<WindowCloseEvent>(
                [this](WindowCloseEvent& e) -> bool
                {
                    this->m_isRunning = false;
                    return true;
                });

            dispatcher.dispatchEvent<KeyPressedEvent>(
                [this](KeyPressedEvent& e) -> bool
                {
                    return true;
                });
            dispatcher.dispatchEvent<WindowResizeEvent>(
                [this](WindowResizeEvent& e) -> bool
                {
                    if (e.getHeight() == 0 || e.getWidth() == 0)
                    {
                        this->m_isMinimised = true;
                        return false;
                    }
                    m_isMinimised = false;
                    Renderer::onWindowResize(e.getWidth(), e.getHeight());
                    return false;
                });

            for (auto it = m_layerStack.end() - 1; it != m_layerStack.begin() - 1; --it)
            {
                (*it)->onEvent(e);
                if (e.isHandled())
                {
                    break;
                }
            }
        } // lambda end
    );    // setEventCallback end

    Renderer::init();

    m_imGuiLayer = new ImGuiLayer{};
    pushOverlay(m_imGuiLayer);
}

void App::run()
{
    while (m_isRunning)
    {
        auto deltaTime = calculateDeltaTime();

        if (!m_isMinimised)
        {
            for (auto layer : m_layerStack)
            {
                layer->onUpdate(deltaTime);
            }
        }
#if defined(GE_DEBUG)
        ImGuiLayer::begin();
        for (auto layer : m_layerStack)
        {
            layer->onImGuiRender();
        }
        ImGuiLayer::end();
#endif

        m_window->onUpdate();
    }
}

void App::pushLayer(Layer* layer)
{
    m_layerStack.pushLayer(layer);
    layer->onAttach();
}

void App::pushOverlay(Layer* layer)
{
    m_layerStack.pushOverlay(layer);
    layer->onAttach();
}

void App::onEvent(Event& e)
{
}

// Private funcs
TimeStep App::calculateDeltaTime()
{
    auto time = static_cast<float>(glfwGetTime());
    TimeStep timeStep{time - m_lastFrameTime};
    m_lastFrameTime = time;
    return timeStep;
}
}