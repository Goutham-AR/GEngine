#pragma once

#include <common.hh>
#include <glm/vec4.hpp>
#include <memory>
#include "VertexArray.hh"

namespace GE
{

class GE_PUBLIC RendererAPI
{
public:
    virtual void init() = 0;
    virtual void clear(const glm::vec4& color) = 0;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;
    virtual void setViewPort(int x, int y, int width, int height) = 0;
};

}