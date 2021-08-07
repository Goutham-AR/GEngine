#include "App.hh"

#include <events/AppEvent.hh>
#include <Logger.hh>

namespace GE
{
App::App()
{
    m_window = Window::create();
}
App::~App()
{
}

void App::run()
{

    while (m_isRunning)
    {
        m_window->onUpdate();
    }
}
}