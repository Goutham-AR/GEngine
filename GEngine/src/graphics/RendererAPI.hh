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
    virtual void clear(const glm::vec4& color) = 0;
    virtual void drawIndexed(const std::shared_ptr<VertexArray>& vao) = 0;
};

}