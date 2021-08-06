#include "Simple2DRenderer.hh"

namespace GE::core
{

Simple2DRenderer::Simple2DRenderer()
    : m_renderQueue{}
{
}

void Simple2DRenderer::attach(const Renderable2D* renderable)
{
    m_renderQueue.push_back(renderable);
}

void Simple2DRenderer::render()
{
    while (!m_renderQueue.empty())
    {
        const auto* renderable = m_renderQueue.front();

        renderable->getVAO()->bind();
        renderable->getIBO()->bind();

        renderable->getShader().setUniform("modelMat", math::mat4::trans(renderable->getPosition()));
        glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

        renderable->getIBO()->unBind();
        renderable->getVAO()->unBind();

        m_renderQueue.pop_front();
    }
}

}