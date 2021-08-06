#include "VertexArray.hh"

namespace GE::core
{

VertexArray::VertexArray()
    : m_handle{},
      m_buffers{}
{
    glGenVertexArrays(1, &m_handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_handle);
    for (auto* buffer : m_buffers)
    {
        delete buffer;
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(m_handle);
}
void VertexArray::unBind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer* vbo, unsigned int index)
{
    bind();
    vbo->bind();

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, vbo->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

    vbo->unBind();
    unBind();

    m_buffers.push_back(vbo);
}

}