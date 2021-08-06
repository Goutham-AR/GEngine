#include "VertexBuffer.hh"

#include <glad/glad.h>

namespace GE::core
{

VertexBuffer::VertexBuffer(float* data, size_t count, unsigned int componentCount)
    : m_handle{},
      m_componentCount{componentCount}
{
    glGenBuffers(1, &m_handle);

    bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
    unBind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void VertexBuffer::unBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}