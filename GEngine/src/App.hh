#pragma once

#include "common.hh"
#include "events/AppEvent.hh"
#include "window/Window.hh"
#include "layers/LayerStack.hh"
#include "layers/ImGui/ImGuiLayer.hh"

#include <memory>

namespace GE
{

class GE_PUBLIC App
{
public:
    App();
    virtual ~App() = default;

    void run();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);
    void onEvent(Event& e);

    static App& get() { return *appInstance; }
    [[nodiscard]] Window& getWindow() const { return *m_window; }

private:
    std::unique_ptr<Window> m_window;
    ImGuiLayer* m_imGuiLayer;
    LayerStack m_layerStack;
    bool m_isRunning = true;

    static App* appInstance;
};

App* createApp();

}