#pragma once

#include <common.hh>
#include <memory>

#include "Buffers.hh"

namespace GE
{

class GE_PUBLIC VertexArray
{
public:
    virtual ~VertexArray() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) = 0;
    virtual void addIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo) = 0;

    [[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
    [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffer() const = 0;

    static VertexArray* create();
};

}