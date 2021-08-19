#pragma once

#include <common.hh>
#include "VertexArray.hh"
#include "RendererAPI.hh"

namespace GE
{

class GE_PUBLIC RenderCommand
{
public:
    static void init()
    {
        s_rendererAPI->init();
    }

    static void clear(const glm::vec4& color)
    {
        s_rendererAPI->clear(color);
    }

    static void setViewPort(int x, int y, int width, int height)
    {
        s_rendererAPI->setViewPort(x, y, width, height);
    }
    static void drawIndexed(const Sptr<VertexArray>& vao)
    {
        s_rendererAPI->drawIndexed(vao);
    }

private:
    static RendererAPI* s_rendererAPI;
};

}