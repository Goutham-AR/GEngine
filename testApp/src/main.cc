#include <GE.hh>

#include <array>

class TestLayer : public GE::Layer
{
public:
    TestLayer()
        : Layer{"TestLayer"},
          m_camera{-1.6f, 1.6f, -0.9f, 0.9f},
          m_camPos{0.0f}
    {
    }

    void onAttach() override
    {

        m_ShaderProgram.reset(GE::Shader::create("assets/vertex.glsl", "assets/fragment.glsl"));

        // Temporary Rendering code
        m_vao.reset(GE::VertexArray::create());

        std::array<float, 21> vertices{
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
        auto vbo = std::shared_ptr<GE::VertexBuffer>(GE::VertexBuffer::create(&vertices[0], sizeof(float) * vertices.size()));
        {
            GE::BufferLayout layout = {
                {GE::ShaderDataType::Float3, "a_position", false},
                {GE::ShaderDataType::Float4, "a_color", false},
            };

            vbo->setLayout(layout);
        }
        m_vao->addVertexBuffer(vbo);

        std::array<std::uint32_t, 3> indices{0, 1, 2};
        auto ibo = std::shared_ptr<GE::IndexBuffer>(GE::IndexBuffer::create(&indices[0], indices.size()));
        m_vao->addIndexBuffer(ibo);

        // second shape
        m_vao2.reset(GE::VertexArray::create());
        std::array<float, 28> vertices2{
            -0.8f, -0.8f, 0.0f, 0.3f, 0.4f, 0.7f, 1.0f,
            -0.8f, 0.8f, 0.0f, 0.9f, 1.0f, 0.2f, 1.0f,
            0.8f, 0.8f, 0.0f, 0.2f, 0.1f, 1.0f, 1.0f,
            0.8f, -0.8f, 0.0f, 0.9f, 0.6f, 1.0f, 1.0f};
        vbo.reset(GE::VertexBuffer::create(&vertices2[0], sizeof(float) * vertices2.size()));
        {
            GE::BufferLayout layout = {
                {GE::ShaderDataType::Float3, "a_position", false},
                {GE::ShaderDataType::Float4, "a_color", false},
            };

            vbo->setLayout(layout);
        }
        m_vao2->addVertexBuffer(vbo);

        std::array<std::uint32_t, 6> indices2{0, 1, 2, 2, 3, 0};
        ibo.reset(GE::IndexBuffer::create(&indices2[0], indices2.size()));
        m_vao2->addIndexBuffer(ibo);
    }
    void onDetach() override
    {
    }

    void onUpdate() override
    {
        if (GE::Input::isKeyPressed(GE::KeyCode::W) || GE::Input::isKeyPressed(GE::KeyCode::UpArrow))
        {
            m_camPos.y -= 0.05f;
        }

        else if (GE::Input::isKeyPressed(GE::KeyCode::S) || GE::Input::isKeyPressed(GE::KeyCode::DownArrow))
        {
            m_camPos.y += 0.05f;
        }

        if (GE::Input::isKeyPressed(GE::KeyCode::A) || GE::Input::isKeyPressed(GE::KeyCode::LeftArrow))
        {
            m_camPos.x += 0.05f;
        }

        else if (GE::Input::isKeyPressed(GE::KeyCode::D) || GE::Input::isKeyPressed(GE::KeyCode::RightArrow))
        {
            m_camPos.x -= 0.05f;
        }
        GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
        m_camera.setPosition(m_camPos);
        // m_camera.setRotation(45.0f);
        GE::Renderer::begin(m_camera);
        GE::Renderer::submit(m_vao2, m_ShaderProgram);
        GE::Renderer::submit(m_vao, m_ShaderProgram);
        GE::Renderer::end();
    }

    void onEvent(GE::Event& event) override
    {
    }

private:
    std::shared_ptr<GE::Shader> m_ShaderProgram;
    std::shared_ptr<GE::VertexArray> m_vao;
    std::shared_ptr<GE::VertexArray> m_vao2;
    GE::OrthoGraphicCamera m_camera;
    glm::vec3 m_camPos;
};

class TestApp : public GE::App
{
public:
    TestApp()
    {
        pushLayer(new TestLayer{});
    }
    ~TestApp() override = default;
};

GE::App* GE::createApp()
{
    return new TestApp{};
}
