#pragma once

#include "common.hh"
#include "events/AppEvent.hh"
#include "graphics/Window.hh"

#include <memory>

namespace GE
{

class GE_PUBLIC App
{
public:
    App();
    virtual ~App() = default;

    void run();

private:
    std::unique_ptr<Window> m_window;
    bool m_isRunning = true;
};

App* createApp();

}