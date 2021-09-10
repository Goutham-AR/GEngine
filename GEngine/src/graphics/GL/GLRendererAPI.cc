#include "GLRendererAPI.hh"
#include <glad/glad.h>

namespace GE
{

void GLRendererAPI::init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void GLRendererAPI::clear(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vao, std::uint32_t count)
{

    if (count == 0)
    {
        glDrawElements(GL_TRIANGLES, vao->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}
void GLRendererAPI::setViewPort(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

}