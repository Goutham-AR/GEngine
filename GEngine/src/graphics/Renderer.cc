#include "Renderer.hh"

#include <graphics/GL/GLShader.hh>

namespace GE
{

OrthoGraphicCamera* Renderer::s_camera = nullptr;

void Renderer::begin(OrthoGraphicCamera& camera)
{
    s_camera = new OrthoGraphicCamera{camera};
}
void Renderer::end()
{
}
void Renderer::submit(const Sptr<VertexArray>& vao, const Sptr<Shader>& shader, const glm::mat4& transformMat)
{
    std::dynamic_pointer_cast<GLShader>(shader)->setUniform("u_viewProjMat", s_camera->getViewProjectionMat());
    std::dynamic_pointer_cast<GLShader>(shader)->setUniform("u_modelMat", transformMat);
    shader->bind();
    vao->bind();
    RenderCommand::drawIndexed(vao);
}

void Renderer::clear(const glm::vec4& color)
{
    RenderCommand::clear(color);
}

}
