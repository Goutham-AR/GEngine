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

    m_deltaTime = timeStep.getSeconds();

    GE::Renderer2D::resetStats();

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
            .Texture = m_texture2,
        };
        GE::Renderer2D::drawQuad(quadInfo);
        quadInfo.Pos = {0.5, 0.8, 0.3};
        quadInfo.Size = {2, 2};
        quadInfo.Color = {0.3, 0.4, 0.5, 1.0};
        quadInfo.Rotation = 45;
        quadInfo.Texture = m_texture;
        quadInfo.TilingFactor = 1;
        GE::Renderer2D::drawQuad(quadInfo);
        quadInfo.Pos = {0.8, 0, 0.5};
        quadInfo.Size = {1, 1};
        quadInfo.TilingFactor = 10;
        quadInfo.Color = {1, 1, 1, 1};
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
            .Texture = m_texture2,
            .Rotation = 32,
        };
        GE::Renderer2D::drawQuad(quadInfo);

        GE::Renderer2D::end();

        GE::Renderer2D::begin(m_cameraController.getCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.05f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.05f)
            {
                glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};

                static GE::Quad quad;
                quad.Pos = {x, y, 0.1};
                quad.Size = {0.45, 0.45};
                quad.Color = color;
                GE::Renderer2D::drawQuad(quad);
            }
        }

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
    ImGui::Begin("Renderer2D stats");
    auto rendererStats = GE::Renderer2D::getStats();
    ImGui::Text("Draw Calls: %d", rendererStats.numDrawCall);
    ImGui::Text("Quad Count: %d", rendererStats.quadCount);
    ImGui::Text("Vertices  : %d", rendererStats.getTotalVertexCount());
    ImGui::Text("Indices   : %d", rendererStats.getTotalIndexCount());
    ImGui::Text("FPS       : %f", 1 / m_deltaTime);
    ImGui::End();

    ImGui::Begin("color picker");
    ImGui::ColorPicker4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}