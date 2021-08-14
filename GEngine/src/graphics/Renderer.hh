#pragma once

#include <common.hh>
#include "VertexArray.hh"
#include "RenderCommand.hh"

namespace GE
{

class GE_PUBLIC Renderer
{

public:
    Renderer() = default;
    virtual ~Renderer() = default;

    static void begin();
    static void end();

    static void submit(const std::shared_ptr<VertexArray>& vao);

    static void clear(const glm::vec4& color);

private:
};

}