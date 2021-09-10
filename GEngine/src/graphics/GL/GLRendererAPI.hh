#pragma once

#include <common.hh>
#include "../Renderer/RendererAPI.hh"

namespace GE
{

class GE_PUBLIC GLRendererAPI : public RendererAPI
{
public:
    void init() override;
    void clear(const Color& color) override;
    void drawIndexed(const std::shared_ptr<VertexArray>& vao) override;
    void setViewPort(int x, int y, int width, int height) override;
};

}