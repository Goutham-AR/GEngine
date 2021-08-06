#include "Renderer2D.hh"

#include <glad/glad.h>
#include <geMath.hh>

#include <deque>

namespace GE::core
{

class Simple2DRenderer : public IRenderer2D
{

public:
    Simple2DRenderer();
    ~Simple2DRenderer() override = default;

    void attach(const Renderable2D* renderable) override;
    void render() override;

private:
    std::deque<const Renderable2D*> m_renderQueue;
};

}