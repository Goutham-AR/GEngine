#include "Buffers.hh"

#include "GL/GLBuffers.hh"

namespace GE
{







VertexBuffer* VertexBuffer::create(float* vertices, std::size_t size)
{
    return new GLVertexBuffer{vertices, size};
        
}

IndexBuffer* IndexBuffer::create(std::uint32_t* indices, std::size_t size)
{
    return new GLIndexBuffer{indices, size};
}

}