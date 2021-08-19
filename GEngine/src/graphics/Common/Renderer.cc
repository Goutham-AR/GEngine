#include "Renderer.hh"
#include "Renderer2D.hh"
#include "../GL/GLShader.hh"

namespace GE
{

OrthoGraphicCamera* Renderer::s_camera = nullptr;

void Renderer::init()
{
    RenderCommand::init();
    Renderer2D::init();
}
void Renderer::onWindowResize(int newWidth, int newHeight)
{
    RenderCommand::setViewPort(0, 0, newWidth, newHeight);
}

void Renderer::begin(const OrthoGraphicCamera& camera)
{
    s_camera = new OrthoGraphicCamera{camera};
}
void Renderer::end()
{
}
void Renderer::submit(const Sptr<VertexArray>& vao, const Sptr<IShader>& shader, const glm::mat4& transformMat)
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
