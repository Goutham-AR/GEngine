#pragma once

#include <common.hh>
#include <cstddef>
#include <cstdint>

namespace GE
{

class GE_PUBLIC VertexBuffer
{
public:
    VertexBuffer() = default;
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static VertexBuffer* create(float* vertices, std::size_t size);
};


class GE_PUBLIC IndexBuffer
{
public:
    IndexBuffer() = default;
    virtual ~IndexBuffer() = default;

    
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual std::uint32_t getCount() const = 0;

    static IndexBuffer* create(std::uint32_t* indices, std::uint32_t count);
};


}