#include "GLBuffers.hh"
#include <glad/glad.h>

namespace GE
{

// -------------------------------------------------------
// ------------------- VertexBuffer -----------------------
// -------------------------------------------------------
GLVertexBuffer::GLVertexBuffer(float* vertices, std::size_t size)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    unbind();
}
GLVertexBuffer::GLVertexBuffer(std::size_t size)
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
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

void GLVertexBuffer::setData(const void* data, std::size_t size)
{
    bind();
    // glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    auto dataStore = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    std::memcpy(dataStore, data, size);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    unbind();
}

void GLVertexBuffer::setLayout(BufferLayout& layout)
{
    m_layout = layout;
}

const BufferLayout& GLVertexBuffer::getLayout() const
{
    return m_layout;
}

// -------------------------------------------------------
// ------------------- IndexBuffer -----------------------
// -------------------------------------------------------
GLIndexBuffer::GLIndexBuffer(std::uint32_t* indices, std::uint32_t count)
    : m_count{count}
{
    glCreateBuffers(1, &m_handle);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), indices, GL_STATIC_DRAW);
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

std::uint32_t GLIndexBuffer::getCount() const
{
    return m_count;
}

}