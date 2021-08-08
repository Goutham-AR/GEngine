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
        m_window->onUpdate();
    }
}

}