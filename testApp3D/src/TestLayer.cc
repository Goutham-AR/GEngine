#include "TestLayer.hh"

TestLayer::TestLayer()
    : Layer{"TestLayer"},
      m_camera{16.0f / 9.0f, 70, 0.01f, 1000.0f}
{
}

void TestLayer::onAttach()
{
    m_texture = GE::Texture2D::create("assets/Textures/brickWall1.jpg");
    m_shader = GE::IShader::create("assets/Shaders/Shader.vert", "assets/Shaders/Shader.frag");
    m_vao = GE::VertexArray::create();

    m_shader->setUniform("u_texture", 0);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0, 0,
        0.5f, -0.5f, -0.5f, 1, 0,
        0.5f, 0.5f, -0.5f, 1, 1,
        -0.5f, 0.5f, -0.5f, 0, 1,
        -0.5f, -0.5f, 0.5f, 0, 0,
        0.5f, -0.5f, 0.5f, 1, 0,
        0.5f, 0.5f, 0.5f, 1, 1,
        -0.5f, 0.5f, 0.5f, 0, 1};
    auto vbo = GE::VertexBuffer::create(vertices, sizeof(vertices));
    GE::BufferLayout layout = {
        {GE::ShaderDataType::Float3, "a_pos", false},
        {GE::ShaderDataType::Float2, "a_texCoord", false},
    };
    vbo->setLayout(layout);
    unsigned int indices[] = {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1};
    auto ibo = GE::IndexBuffer::create(indices, 36);
    m_vao->addVertexBuffer(vbo);
    m_vao->addIndexBuffer(ibo);
}
void TestLayer::onDetach()
{
}
void TestLayer::onUpdate(GE::TimeStep& deltaTime)
{
    m_texture->bind(0);
    m_camera.setPosition(m_camPos);
    m_shader->setUniform("u_viewProjMat", m_camera.getViewProjectionMat());
    m_shader->setUniform("u_modelMat", glm::mat4{1.0f});
    GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
    GE::Renderer::submit(m_vao, m_shader);
}
void TestLayer::onEvent(GE::Event& event)
{
}
void TestLayer::onImGuiRender()
{
    ImGui::Begin("Camera Settings");
    ImGui::SliderFloat3("camera Positiohn", glm::value_ptr(m_camPos), -8.0f, 8.0f);
    ImGui::End();
}