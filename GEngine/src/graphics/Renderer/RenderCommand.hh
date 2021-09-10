#pragma once

#include <common.hh>
#include "../Common/VertexArray.hh"
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
    static void drawIndexed(const Sptr<VertexArray>& vao, std::uint32_t count = 0)
    {
        s_rendererAPI->drawIndexed(vao, count);
    }

private:
    static RendererAPI* s_rendererAPI;
};

}