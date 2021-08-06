#pragma once

#include <cstddef>


namespace GE::core
{

class VertexBuffer
{
public:
    explicit VertexBuffer(float* data, size_t count, unsigned int componentCount);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    void bind() const;
    void unBind() const;

    [[nodiscard]] unsigned int getComponentCount() const { return m_componentCount; }

private:
    unsigned int m_handle;
    unsigned int m_componentCount;
};

}