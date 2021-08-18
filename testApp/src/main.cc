#include "glm/gtc/type_ptr.hpp"
#include <GE.hh>

#include <graphics/GL/GLShader.hh> // temp

#include <array>

class TestLayer : public GE::Layer
{
public:
    TestLayer()
        : Layer{"TestLayer"},
          m_cameraController{16.0f / 9}
    {

        m_shaderLib.load("assets/Shaders/default.vert", "assets/Shaders/default.frag");
        m_shaderLib.load("assets/Shaders/texShader.vert", "assets/Shaders/texShader.frag");

        m_tex2D = GE::Texture2D::create("assets/Textures/brickWall1.jpg");
        m_transparentTex = GE::Texture2D::create("assets/Textures/ChernoLogo.png");

        // Temporary Rendering code
        m_vao = GE::VertexArray::create();
        std::vector<float> vertices{
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};
        auto vbo = GE::Sptr<GE::VertexBuffer>(GE::VertexBuffer::create(&vertices[0], sizeof(float) * vertices.size()));
        {
            GE::BufferLayout layout = {
                {GE::ShaderDataType::Float3, "a_position", false},
            };

            vbo->setLayout(layout);
        }
        m_vao->addVertexBuffer(vbo);

        std::vector<std::uint32_t> indices{0, 1, 2};
        auto ibo = GE::Sptr<GE::IndexBuffer>(GE::IndexBuffer::create(&indices[0], indices.size()));
        m_vao->addIndexBuffer(ibo);

        // second shape
        m_vao2 = GE::VertexArray::create();
        std::vector<float> vertices2{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
        vbo = GE::VertexBuffer::create(&vertices2[0], sizeof(float) * vertices2.size());
        {
            GE::BufferLayout layout = {
                {GE::ShaderDataType::Float3, "a_position", false},
                {GE::ShaderDataType::Float2, "a_texCoord", false},
            };

            vbo->setLayout(layout);
        }
        m_vao2->addVertexBuffer(vbo);

        std::vector<std::uint32_t> indices2{0, 1, 2, 2, 3, 0};
        ibo = GE::IndexBuffer::create(&indices2[0], indices2.size());
        m_vao2->addIndexBuffer(ibo);
    }

    void onAttach() override
    {
    }
    void onDetach() override
    {
    }

    void onUpdate(GE::TimeStep& timeStep) override
    {

        m_cameraController.onUpdate(timeStep);

        GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
        GE::Renderer::begin(m_cameraController.getCamera());

        static auto scaleVec = glm::vec3{0.1f, 0.1f, 0.1f};
        static auto scale = glm::scale(glm::mat4{1.0f}, scaleVec);

        std::dynamic_pointer_cast<GE::GLShader>(m_shaderLib.getShader("default"))->setUniform("u_color", m_color);

        for (auto i = 0; i < 10; ++i)
        {
            for (auto j = 0; j < 10; ++j)
            {
                auto transform = glm::translate(glm::mat4{1.0f}, glm::vec3{i * 0.11, j * 0.11f, 0.2f}) * scale;
                GE::Renderer::submit(m_vao2, m_shaderLib.getShader("default"), transform);
            }
        }
        std::dynamic_pointer_cast<GE::GLShader>(m_shaderLib.getShader("texShader"))->setUniform("u_texture", 0);
        m_tex2D->bind(0);
        GE::Renderer::submit(m_vao2, m_shaderLib.getShader("texShader"));
        m_transparentTex->bind(0);
        GE::Renderer::submit(m_vao2, m_shaderLib.getShader("texShader"));

        // GE::Renderer::submit(m_vao, m_ShaderProgram);
        GE::Renderer::end();
    }

    void onEvent(GE::Event& event) override
    {
        m_cameraController.onEvent(event);
    }

    void onImGuiRender() override
    {
    }

private:
    GE::ShaderLibrary m_shaderLib;
    GE::Sptr<GE::Texture2D> m_tex2D, m_transparentTex;
    GE::Sptr<GE::VertexArray> m_vao;
    GE::Sptr<GE::VertexArray> m_vao2;
    GE::OrthoCameraController m_cameraController;
    glm::vec4 m_color{0.2f, 0.6f, 0.9f, 1.0f};
};

class TestApp : public GE::App
{
public:
    TestApp()
    {
        pushOverlay(new TestLayer{});
    }
    ~TestApp() override = default;
};

GE::App* GE::createApp()
{
    return new TestApp{};
}
