#pragma once

#include <GE.hh>

#include "glm/gtc/type_ptr.hpp"
#include <graphics/GL/GLShader.hh> // temp

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
    GE::ShaderLibrary m_shaderLib;
    GE::Sptr<GE::Texture2D> m_tex2D, m_transparentTex;
    GE::Sptr<GE::VertexArray> m_vao;
    GE::Sptr<GE::VertexArray> m_vao2;
    GE::OrthoCameraController m_cameraController;
    glm::vec4 m_color{0.2f, 0.6f, 0.9f, 1.0f};
};
