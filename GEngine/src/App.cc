#include "App.hh"

#include <glad/glad.h>

#include "window/Input.hh"
#include "window/KeyCode.hh"
#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>

#include <Logger.hh>

namespace GE
{
App* App::appInstance = nullptr;

App::App()
{
    GE_ASSERT(!appInstance, "Only one App can exist");
    appInstance = this;

    m_window = Window::create();

    m_window->setEventCallback(
        [this](Event& e) {
            EventDispatcher dispatcher{e};

            dispatcher.dispatchEvent<WindowCloseEvent>(
                [this](WindowCloseEvent& e) -> bool {
                    this->m_isRunning = false;
                    return true;
                });

            dispatcher.dispatchEvent<KeyPressedEvent>(
                [this](KeyPressedEvent& e) -> bool {
                    // ENGINE_LOG_TRACE("{0}", e.getKeyCode());
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

            // ENGINE_LOG_TRACE("{0}", e);
        });

    m_imGuiLayer = new ImGuiLayer{};
    pushOverlay(m_imGuiLayer);
}

void App::run()
{
    while (m_isRunning)
    {
        glClearColor(0.3f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto* layer : m_layerStack)
        {
            layer->onUpdate();
        }

        m_imGuiLayer->begin();
        // m_imGuiLayer->onImGuiRender();
        for (auto* layer : m_layerStack)
        {
            layer->onImGuiRender();
        }
        m_imGuiLayer->end();

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

}