#include "App.hh"

#include "window/Input.hh"
#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>
#include <glad/glad.h>

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto* layer : m_layerStack)
        {
            layer->onUpdate();
        }

        auto [x, y] = Input::getMousePos();
        LOG_TRACE("({0}, {1})", x, y);

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