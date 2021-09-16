#pragma once

// cpp std
#include <memory>

#include "common.hh"
#include "events/AppEvent.hh"
#include "window/Window.hh"
#include "layers/LayerStack.hh"
#include "layers/ImGui/ImGuiLayer.hh"

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

    static App& get() { return *appInstance; }
    [[nodiscard]] Window& getWindow() const { return *m_window; }

    void close() { m_isRunning = false; }

private:
    Uptr<Window> m_window;
    ImGuiLayer* m_imGuiLayer;
    LayerStack m_layerStack;
    bool m_isRunning = true;
    bool m_isMinimised = false;
    float m_lastFrameTime = 0.0f;

private:
    static App* appInstance;

private:
    TimeStep calculateDeltaTime();
};

App* createApp();

}