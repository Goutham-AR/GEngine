#include "glm/gtc/type_ptr.hpp"
#include <GE.hh>

#include <graphics/GL/GLShader.hh> // temp

#include <array>

class TestLayer : public GE::Layer
{
public:
    TestLayer()
        : Layer{"TestLayer"},
          m_camera{-1.6f, 1.6f, -0.9f, 0.9f},
          m_camPos{0.0f}
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
        auto deltaTime = timeStep.getSeconds();

        handleInput(deltaTime);

        GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
        m_camera.setPosition(m_camPos);
        m_camera.setRotation(m_camRot * (180 / 3.14));
        GE::Renderer::begin(m_camera);

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
    }

    void onImGuiRender() override
    {
        ImGui::Begin("settings");
        ImGui::ColorEdit4("Square Color", glm::value_ptr(m_color));
        ImGui::SliderAngle("Camera Rotation", &m_camRot);
        ImGui::SliderFloat3("Camera Position", glm::value_ptr(m_camPos), -1.6f, 1.6f);
        ImGui::End();
    }

private:
    GE::ShaderLibrary m_shaderLib;
    GE::Sptr<GE::Texture2D> m_tex2D, m_transparentTex;
    GE::Sptr<GE::VertexArray> m_vao;
    GE::Sptr<GE::VertexArray> m_vao2;
    GE::OrthoGraphicCamera m_camera;
    glm::vec3 m_camPos;
    float m_camRot{};
    glm::vec4 m_color{0.2f, 0.6f, 0.9f, 1.0f};

private:
    inline void handleInput(float deltaTime)
    {
        if (GE::Input::isKeyPressed(GE::KeyCode::W) || GE::Input::isKeyPressed(GE::KeyCode::UpArrow))
        {
            m_camPos.y -= 1.0f * deltaTime;
        }
        else if (GE::Input::isKeyPressed(GE::KeyCode::S) || GE::Input::isKeyPressed(GE::KeyCode::DownArrow))
        {
            m_camPos.y += 1.0f * deltaTime;
        }

        if (GE::Input::isKeyPressed(GE::KeyCode::A) || GE::Input::isKeyPressed(GE::KeyCode::LeftArrow))
        {
            m_camPos.x += 1.0f * deltaTime;
        }

        else if (GE::Input::isKeyPressed(GE::KeyCode::D) || GE::Input::isKeyPressed(GE::KeyCode::RightArrow))
        {
            m_camPos.x -= 1.0f * deltaTime;
        }
    }
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
