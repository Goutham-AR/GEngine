#include "App.hh"

#include <array>

#include <Logger.hh>
#include <window/Input.hh>
#include <window/KeyCode.hh>
#include <events/AppEvent.hh>
#include <events/KeyEvent.hh>
#include <graphics/Renderer.hh>

namespace GE
{
// singleton
App* App::appInstance = nullptr;

App::App()
    : m_imGuiLayer{nullptr},
      m_layerStack{},
      m_camera{-1.6f, 1.6f, -0.9f, 0.9f}
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
                    switch (e.getKeyCode())
                    {
                    case KeyCode::W:
                    {
                        auto newY = m_camera.getPosition().y + 0.1;
                        m_camera.setPosition({m_camera.getPosition().x, newY, 0.0f});
                        break;
                    }
                    case KeyCode::S:
                    {
                        auto newY = m_camera.getPosition().y - 0.1;
                        m_camera.setPosition({m_camera.getPosition().x, newY, 0.0f});
                        break;
                    }
                    }
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
    m_vao.reset(VertexArray::create());

    std::array<float, 21> vertices{
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
    auto vbo = std::shared_ptr<VertexBuffer>(VertexBuffer::create(&vertices[0], sizeof(float) * vertices.size()));
    {
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_position", false},
            {ShaderDataType::Float4, "a_color", false},
        };

        vbo->setLayout(layout);
    }
    m_vao->addVertexBuffer(vbo);

    std::array<std::uint32_t, 3> indices{0, 1, 2};
    auto ibo = std::shared_ptr<IndexBuffer>(IndexBuffer::create(&indices[0], indices.size()));
    m_vao->addIndexBuffer(ibo);

    // second shape
    m_vao2.reset(VertexArray::create());
    std::array<float, 28> vertices2{
        -0.8f, -0.8f, 0.0f, 0.3f, 0.4f, 0.7f, 1.0f,
        -0.8f, 0.8f, 0.0f, 0.9f, 1.0f, 0.2f, 1.0f,
        0.8f, 0.8f, 0.0f, 0.2f, 0.1f, 1.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 0.9f, 0.6f, 1.0f, 1.0f};
    vbo.reset(VertexBuffer::create(&vertices2[0], sizeof(float) * vertices2.size()));
    {
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_position", false},
            {ShaderDataType::Float4, "a_color", false},
        };

        vbo->setLayout(layout);
    }
    m_vao2->addVertexBuffer(vbo);

    std::array<std::uint32_t, 6> indices2{0, 1, 2, 2, 3, 0};
    ibo.reset(IndexBuffer::create(&indices2[0], indices2.size()));
    m_vao2->addIndexBuffer(ibo);
}

void App::run()
{
    while (m_isRunning)
    {

        // m_camera.setPosition({(m_window->getWidth() - Input::getMousePosX()) / m_window->getWidth(), (m_window->getHeight() - Input::getMousePosY()) / m_window->getHeight(), 0.0f});
        // m_camera.setRotation(45.0f);
        RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
        Renderer::begin(m_camera);
        Renderer::submit(m_vao2, m_ShaderProgram);
        Renderer::submit(m_vao, m_ShaderProgram);
        Renderer::end();

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