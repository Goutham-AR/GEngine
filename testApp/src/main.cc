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
    }

    void onAttach() override
    {

        m_ShaderProgram.reset(GE::Shader::create("assets/vertex.glsl", "assets/fragment.glsl"));
        m_tex2D = GE::Texture2D::create("assets/Textures/brickWall1.jpg");
        m_texShaderProgram.reset(GE::Shader::create("assets/texShader.vert", "assets/texShader.frag"));

        // Temporary Rendering code
        m_vao.reset(GE::VertexArray::create());

        std::array<float, 9> vertices{
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

        std::array<std::uint32_t, 3> indices{0, 1, 2};
        auto ibo = GE::Sptr<GE::IndexBuffer>(GE::IndexBuffer::create(&indices[0], indices.size()));
        m_vao->addIndexBuffer(ibo);

        // second shape
        m_vao2.reset(GE::VertexArray::create());
        std::array<float, 20> vertices2{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
        vbo.reset(GE::VertexBuffer::create(&vertices2[0], sizeof(float) * vertices2.size()));
        {
            GE::BufferLayout layout = {
                {GE::ShaderDataType::Float3, "a_position", false},
                {GE::ShaderDataType::Float2, "a_texCoord", false},
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

    void onUpdate(GE::TimeStep& timeStep) override
    {
        // LOG_TRACE("Delta Time: {0}s ({1}ms)", timeStep.getSeconds(), timeStep.getMilliSeconds());

        auto deltaTime = timeStep.getSeconds();

        handleInput(deltaTime);

        GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
        m_camera.setPosition(m_camPos);
        m_camera.setRotation(m_camRot * (180 / 3.14));
        GE::Renderer::begin(m_camera);

        static auto scaleVec = glm::vec3{0.1f, 0.1f, 0.1f};
        static auto scale = glm::scale(glm::mat4{1.0f}, scaleVec);

        std::dynamic_pointer_cast<GE::GLShader>(m_ShaderProgram)->setUniform("u_color", m_color);

        for (auto i = 0; i < 10; ++i)
        {
            for (auto j = 0; j < 10; ++j)
            {
                auto transform = glm::translate(glm::mat4{1.0f}, glm::vec3{i * 0.11, j * 0.11f, 0.2f}) * scale;
                GE::Renderer::submit(m_vao2, m_ShaderProgram, transform);
            }
        }
        m_tex2D->bind(0);
        std::dynamic_pointer_cast<GE::GLShader>(m_texShaderProgram)->setUniform("u_texture", 0);
        GE::Renderer::submit(m_vao2, m_texShaderProgram);

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
    GE::Sptr<GE::Shader> m_ShaderProgram;
    GE::Sptr<GE::Shader> m_texShaderProgram;
    GE::Sptr<GE::Texture2D> m_tex2D;
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
