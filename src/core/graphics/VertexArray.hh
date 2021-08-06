#pragma once

#include <glad/glad.h>

#include <vector>

#include "VertexBuffer.hh"

namespace GE::core
{

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void bind() const;
    void unBind() const;

    void addBuffer(VertexBuffer* vbo, unsigned int index);

private:
    unsigned int m_handle;
    std::vector<VertexBuffer*> m_buffers;
};

}