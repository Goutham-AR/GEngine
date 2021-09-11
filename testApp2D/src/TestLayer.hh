#pragma once

#include <GE.hh>

class TestLayer : public GE::Layer
{
public:
    TestLayer();

    void onAttach() override;
    void onDetach() override;
    void onUpdate(GE::TimeStep& timeStep) override;

    void onEvent(GE::Event& event) override;
    void onImGuiRender() override;

private:
    GE::Sptr<GE::IShader> m_shader;
    GE::Sptr<GE::VertexArray> m_vao;
    GE::Sptr<GE::Texture2D> m_texture;
    GE::Sptr<GE::Texture2D> m_texture2;
    GE::OrthoCameraController m_cameraController;
    glm::vec4 m_squareColor{0.2f, 0.6f, 0.9f, 1.0f};

    float m_deltaTime;
};
