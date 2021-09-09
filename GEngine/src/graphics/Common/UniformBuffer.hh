#pragma once

#include "common.hh"
#include <glad/glad.h>

namespace GE
{

inline GLintptr uniformBufferByteSize(GLsizeiptr size)
{
    return (size + GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT) & ~GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT;
}

template <typename T>
class GE_PUBLIC UniformBuffer
{
public:
    UniformBuffer() = default;
    virtual ~UniformBuffer() = default;

    virtual void setData(const T* data) = 0;

    static Sptr<UniformBuffer<T>> create(unsigned int index);
};

template <typename T>
class GLUniformBuffer : public UniformBuffer<T>
{
public:
    GLUniformBuffer(unsigned int index)
        : m_bufferSize{sizeof(T)}
    {
        glCreateBuffers(1, &m_handle);
        glNamedBufferStorage(m_handle, m_bufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
        glBindBufferRange(GL_UNIFORM_BUFFER, index, m_handle, m_offset, m_bufferSize);
        m_offset = s_currentOffset;
        s_currentOffset += uniformBufferByteSize(m_bufferSize);
    }
    ~GLUniformBuffer()
    {
        glDeleteBuffers(1, &m_handle);
    }

    void setData(const T* data) override
    {
        glNamedBufferSubData(m_handle, m_offset, m_bufferSize, data);
    }

private:
    GLuint m_handle{};
    GLsizeiptr m_bufferSize{};
    GLintptr m_offset{};

    static GLintptr s_currentOffset;
};

template <typename T>
GLintptr GLUniformBuffer<T>::s_currentOffset = 0;

template <typename T>
Sptr<UniformBuffer<T>> UniformBuffer<T>::create(unsigned int index)
{
    return std::make_shared<GLUniformBuffer<T>>(index);
}

}