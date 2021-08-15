#include "Renderer.hh"

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
void Renderer::submit(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Shader>& shader)
{
    shader->setUniform("u_viewProjMat", s_camera->getViewProjectionMat());
    shader->bind();
    vao->bind();
    RenderCommand::drawIndexed(vao);
}

void Renderer::clear(const glm::vec4& color)
{
    RenderCommand::clear(color);
}

}
