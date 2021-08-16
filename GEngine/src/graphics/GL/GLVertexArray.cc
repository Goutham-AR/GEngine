#include "GLVertexArray.hh"

namespace GE
{
GLVertexArray::GLVertexArray()
{
    glCreateVertexArrays(1, &m_handle);
}

GLVertexArray::~GLVertexArray()
{
    glDeleteVertexArrays(1, &m_handle);
}

void GLVertexArray::bind() const
{
    glBindVertexArray(m_handle);
}

void GLVertexArray::unbind() const
{
    glBindVertexArray(0);
}

void GLVertexArray::addVertexBuffer(const Sptr<VertexBuffer>& vbo)
{
    this->bind();
    vbo->bind();
    auto index = 0;
    auto layout = vbo->getLayout();
    for (auto& elem : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            elem.getPerVertexCount(),
            ShaderDataTypeToGLtype(elem.type),
            elem.isNormalized ? GL_TRUE : GL_FALSE,
            layout.getStride(),
            reinterpret_cast<const void*>(elem.offset));

        ++index;
    }

    m_vbos.push_back(vbo);
    this->unbind();
}
void GLVertexArray::addIndexBuffer(const Sptr<IndexBuffer>& ibo)
{
    m_ibo = ibo;
    this->bind();
    m_ibo->bind();
    this->unbind();
}

}