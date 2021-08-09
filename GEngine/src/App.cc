#include "App.hh"

#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>

#include <Logger.hh>

namespace GE
{
App::App()
{
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
                    ENGINE_LOG_TRACE("{0}", e.getKeyCode());
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
}
// App::~App()
// {
// }

void App::run()
{
    while (m_isRunning)
    {
        for (auto* layer : m_layerStack)
        {
            layer->onUpdate();
        }

        m_window->onUpdate();
    }
}

void App::pushLayer(Layer* layer)
{
    m_layerStack.pushLayer(layer);
}

void App::pushOverlay(Layer* layer)
{
    m_layerStack.pushOverlay(layer);
}

}