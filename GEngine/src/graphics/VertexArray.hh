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

    virtual void addVertexBuffer(const Sptr<VertexBuffer>& vbo) = 0;
    virtual void addIndexBuffer(const Sptr<IndexBuffer>& ibo) = 0;

    [[nodiscard]] virtual const Sptr<IndexBuffer>& getIndexBuffer() const = 0;
    [[nodiscard]] virtual const std::vector<Sptr<VertexBuffer>>& getVertexBuffer() const = 0;

    static Sptr<VertexArray> create();
};

}