#pragma once

#include <GE.hh>

class TestLayer : public GE::Layer
{
public:
    TestLayer();
    ~TestLayer() override = default;

    void onAttach() override;
    void onDetach() override;
    void onUpdate(GE::TimeStep& deltaTime) override;
    void onEvent(GE::Event& event) override;
    void onImGuiRender() override;

private:
    GE::Sptr<GE::IShader> m_shader;
    GE::Sptr<GE::VertexArray> m_vao;
    GE::Sptr<GE::Texture2D> m_texture;
    GE::PerspectiveCamera m_camera;
    glm::vec3 m_camPos{0, 0, -8.0f};
};