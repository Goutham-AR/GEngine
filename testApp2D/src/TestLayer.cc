#include "TestLayer.hh"

TestLayer::TestLayer()
    : Layer{"TestLayer"},
      m_cameraController{16.0f / 9}
{
}

void TestLayer::onAttach()
{
    m_texture = GE::Texture2D::create("assets/Textures/brickWall1.jpg");
    m_texture2 = GE::Texture2D::create("assets/Textures/brickWall3.jpg");
}

void TestLayer::onDetach()
{
    GE::Renderer2D::shutdown();
    // free all the assets
}

void TestLayer::onUpdate(GE::TimeStep& timeStep)
{
    GE_PROFILE_FUNC();

    {
        GE_PROFILE_SCOPE("CameraController::onUpdate");
        m_cameraController.onUpdate(timeStep);
    }
    {
        GE_PROFILE_SCOPE("RenderCommand::clear");
        GE::RenderCommand::clear(glm::vec4{0.1f, 0.1f, 0.1f, 1.0f});
    }
    {
        GE_PROFILE_SCOPE("Renderer Draw");
        GE::Renderer2D::begin(m_cameraController.getCamera());
        GE::Renderer2D::drawQuad({0, 0, 0.2}, {1, 1}, m_squareColor);
        GE::Renderer2D::drawQuad({2.0f, 0.7f, 0.2}, {1, 1}, m_squareColor);
        GE::Renderer2D::drawQuad({-0.7f, -0.3, 0}, {10, 10}, m_texture);
        GE::Renderer2D::drawRotatedQuad({3, 2, 0.5}, {3, 3}, m_texture2, 45.0f);
        GE::Renderer2D::drawRotatedQuad({3, 2, 0.5}, {3, 3}, GE::Color{.4f, .6, .9, 1.0f}, 45.0f);
        GE::Renderer2D::drawRotatedTintedQuad({-2, -3, 0.3}, {1, 1}, m_texture, GE::Color{0, 1, 0, 1}, 32.0f);
        GE::Renderer2D::end();
    }
}

void TestLayer::onEvent(GE::Event& event)
{
    m_cameraController.onEvent(event);
}

void TestLayer::onImGuiRender()
{
    GE_PROFILE_FUNC();
    ImGui::Begin("color picker");
    ImGui::ColorPicker4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}