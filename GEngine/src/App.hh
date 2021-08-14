#pragma once

// cpp std
#include <memory>

#include "common.hh"
#include "events/AppEvent.hh"
#include "window/Window.hh"
#include "layers/LayerStack.hh"
#include "layers/ImGui/ImGuiLayer.hh"

#include <graphics/Shader.hh>
#include <graphics/Buffers.hh>
#include <graphics/VertexArray.hh>

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

    // Temporary (Should be abstracted into a renderer)
private:
    std::unique_ptr<Shader> m_ShaderProgram;
    std::unique_ptr<VertexArray> m_vao;
    // std::shared_ptr<VertexBuffer> m_vbo;
    // std::shared_ptr<IndexBuffer> m_ibo;

    std::unique_ptr<VertexArray> m_vao2;
};

App* createApp();

}