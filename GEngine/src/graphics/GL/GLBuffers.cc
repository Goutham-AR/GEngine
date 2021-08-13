#include "GLBuffers.hh"
#include <glad/glad.h>

namespace GE
{

GLVertexBuffer::GLVertexBuffer(float* vertices, std::size_t size)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbind();
}

GLVertexBuffer::~GLVertexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void GLVertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

void GLVertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLIndexBuffer::GLIndexBuffer(std::uint32_t* indices, std::size_t size)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    unbind();
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &m_handle);
}

void GLIndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

void GLIndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



}