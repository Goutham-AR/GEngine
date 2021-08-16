#include "App.hh"

#include <array>

#include <utils/Logger.hh>
#include <window/Input.hh>
#include <window/KeyCode.hh>
#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>
#include <Time.hh>

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

    m_imGuiLayer = new ImGuiLayer{};
    pushOverlay(m_imGuiLayer);
}

void App::run()
{
    while (m_isRunning)
    {
        float time = glfwGetTime();
        TimeStep timeStep{time - m_lastFrameTime};
        m_lastFrameTime = time;

        for (auto layer : m_layerStack)
        {
            layer->onUpdate(timeStep);
        }

        ImGuiLayer::begin();
        for (auto layer : m_layerStack)
        {
            layer->onImGuiRender();
        }
        ImGuiLayer::end();

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

}