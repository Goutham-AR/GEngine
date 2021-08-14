#include "Renderer.hh"

namespace GE
{

void Renderer::begin()
{
}
void Renderer::end()
{
}
void Renderer::submit(const std::shared_ptr<VertexArray>& vao)
{
    vao->bind();
    RenderCommand::drawIndexed(vao);
}

void Renderer::clear(const glm::vec4& color)
{
    RenderCommand::clear(color);
}

}
