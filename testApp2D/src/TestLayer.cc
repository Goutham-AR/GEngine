#include "TestLayer.hh"

TestLayer::TestLayer()
    : Layer{"TestLayer"},
      m_cameraController{16.0f / 9}
{
}

void TestLayer::onAttach()
{
    m_texture = GE::Texture2D::create("assets/Textures/brickWall1.jpg");
}

void TestLayer::onDetach()
{
    GE::Renderer2D::shutdown();
    // free all the assets
}

void TestLayer::onUpdate(GE::TimeStep& timeStep)
{

    m_cameraController.onUpdate(timeStep);

    GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
    GE::Renderer2D::begin(m_cameraController.getCamera());
    GE::Renderer2D::drawQuad({0, 0, 0}, {1, 1}, m_squareColor);
    GE::Renderer2D::drawQuad({2.0f, 0.7f, 0}, {1, 1}, m_squareColor);
    GE::Renderer2D::drawQuad({-0.7f, -0.3, 0}, {10, 10}, m_texture);
    GE::Renderer2D::end();
}

void TestLayer::onEvent(GE::Event& event)
{
    m_cameraController.onEvent(event);
}

void TestLayer::onImGuiRender()
{
    ImGui::Begin("color picker");
    ImGui::ColorPicker4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}