#pragma once

#include <common.hh>
#include "VertexArray.hh"
#include "RendererAPI.hh"

namespace GE
{

class GE_PUBLIC RenderCommand
{
public:
    static void clear(const glm::vec4& color)
    {
        s_rendererAPI->clear(color);
    }
    static void drawIndexed(const std::shared_ptr<VertexArray>& vao)
    {
        s_rendererAPI->drawIndexed(vao);
    }

private:
    static RendererAPI* s_rendererAPI;
};

}