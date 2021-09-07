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
        GE::Quad quadInfo = {
            .Pos = {0, 0, 0.2},
            .Size = {1, 1},
            .Color = m_squareColor,
        };
        GE::Renderer2D::drawQuad(quadInfo);
        quadInfo = {
            .Pos = {2.0f, 0.7f, 0.2f},
            .Size = {1, 1},
            .Color = m_squareColor,
            .Rotation = 32,
        };
        GE::Renderer2D::drawQuad(quadInfo);

        quadInfo = {
            .Pos = {-0.7f, -0.3, 0},
            .Size = {10, 10},
            .Texture = m_texture,
            .TilingFactor = 4,
        };
        GE::Renderer2D::drawQuad(quadInfo);

        quadInfo = {
            .Pos = {-2, -3, 0.3},
            .Size = {1, 1},
            .Color = GE::Color{0, 1, 0, 1},
            .Texture = m_texture,
            .Rotation = 32,
        };
        GE::Renderer2D::drawQuad(quadInfo);

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