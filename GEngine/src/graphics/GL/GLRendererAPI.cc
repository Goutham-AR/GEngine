#include "GLRendererAPI.hh"
#include <glad/glad.h>

namespace GE
{

void GLRendererAPI::clear(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vao)
{
    glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}
}