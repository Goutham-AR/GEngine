#include "TestLayer.hh"

static const std::uint32_t s_mapWidth = 24;
static const std::uint32_t s_mapHeight = 11;

static const char* s_mapTiles = "wwwwwwwwwwwwwwwwwwwwwwww"
                                "wwwwDDDDDDDDDDDwwwwwwwww"
                                "wwwwDDDDwwwwwwDDDDwwwwww"
                                "wwwDDDwwwwwwwwwwDDDwwwwww"
                                "wwDDwwwwGGGGGGwwwDDwwwww"
                                "wDDwwwwwGGGGGwwwwwDwwwww"
                                "wwDDwwwwGGGGGGwwwDwwwwww"
                                "wwwDDDwwwwwwwwwDDDwwwwww"
                                "wwwwwwDDDDDDDDDwwwwwwwww"
                                "wwwwwwwwwwwwwwwwwwwwwwww"
                                "wwwwwwwwwwwwwwwwwwwwwwww";

TestLayer::TestLayer()
    : Layer{"TestLayer"},
      m_cameraController{16.0f / 9}
{
}

void TestLayer::onAttach()
{
    m_texture = GE::Texture2D::create("assets/Textures/brickWall1.jpg");
    m_texture2 = GE::Texture2D::create("assets/Textures/brickWall3.jpg");
    m_spriteSheet = GE::Texture2D::create("assets/Textures/RPG2x.png");

    m_textureMap['D'] = GE::SubTexture2D::createFromCoords(m_spriteSheet, {6, 11}, {128, 128});
    m_textureMap['w'] = GE::SubTexture2D::createFromCoords(m_spriteSheet, {11, 11}, {128, 128});
    m_textureMap['G'] = GE::SubTexture2D::createFromCoords(m_spriteSheet, {1, 11}, {128, 128});
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

        // drawTest(timeStep);

        GE::Quad quad{};
        for (std::uint32_t y = 0; y < s_mapHeight; ++y)
        {
            for (std::uint32_t x = 0; x < s_mapWidth; ++x)
            {
                auto c = s_mapTiles[x + y * s_mapWidth];
                quad.Texture = m_spriteSheet;
                quad.SubTexture = m_textureMap[c];
                quad.Size = {1, 1};
                quad.Pos = {x - s_mapWidth / 2.0f, y - s_mapHeight / 2.0f, 0};

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

    static bool dockSpaceOpen = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
            ImGui::MenuItem("Padding", NULL, &opt_padding);
            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
            {
                GE::App::get().close();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

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
    auto texId = m_texture->getHandle();
    ImGui::Image((void*)texId, ImVec2{64.0f, 64.0f});
    ImGui::End();

    ImGui::End();
}

void TestLayer::drawTest(GE::TimeStep& timeStep)
{
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
    for (float y = -5.0f; y < 5.0f; y += 0.5f)
    {
        for (float x = -5.0f; x < 5.0f; x += 0.5f)
        {
            glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};

            static GE::Quad quad;
            quad.Pos = {x, y, 0.1};
            quad.Size = {0.45, 0.45};
            quad.Color = color;
            GE::Renderer2D::drawQuad(quad);
        }
    }
}