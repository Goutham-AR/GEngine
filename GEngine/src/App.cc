#include "App.hh"

#include <glad/glad.h>

#include "window/Input.hh"
#include "window/KeyCode.hh"
#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>

#include <Logger.hh>

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
        } // lambda end
    );    // setEventCallback end

    m_imGuiLayer = new ImGuiLayer{};
    pushOverlay(m_imGuiLayer);

    m_ShaderProgram.reset(Shader::create("assets/vertex.glsl", "assets/fragment.glsl"));

    // Temporary Rendering code
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    m_vbo = std::unique_ptr<VertexBuffer>{VertexBuffer::create(vertices, sizeof(vertices))};
    m_vbo->bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    unsigned int indices[] = {
        0, 1, 2
    };
    m_ibo.reset(IndexBuffer::create(indices, sizeof(indices)));
    m_ibo->bind();
}

void App::run()
{
    while (m_isRunning)
    {
        // temp, should be replaced after making a renderer
        glClearColor(0.3f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_ShaderProgram->bind();
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        for (auto layer : m_layerStack)
        {
            layer->onUpdate();
        }

        m_imGuiLayer->begin();
        for (auto layer : m_layerStack)
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

void App::onEvent(Event& e)
{
}

}