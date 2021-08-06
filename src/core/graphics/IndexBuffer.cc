#include "IndexBuffer.hh"

#include <glad/glad.h>



namespace GE::core
{

IndexBuffer::IndexBuffer(std::uint16_t* data, size_t count)
    : m_handle{},
      m_count{count}
{
    glGenBuffers(1, &m_handle);

    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint16_t), data, GL_STATIC_DRAW);
    unBind();
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void IndexBuffer::unBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}