#include "Buffers.hh"

#include "GL/GLBuffers.hh"

namespace GE
{

std::uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
        return sizeof(float);
    case ShaderDataType::Float2:
        return 2 * sizeof(float);
    case ShaderDataType::Float3:
        return 3 * sizeof(float);
    case ShaderDataType::Float4:
        return 4 * sizeof(float);
    case ShaderDataType::Mat3:
        return 3 * 3 * sizeof(float);
    case ShaderDataType::Mat4:
        return 4 * 4 * sizeof(float);
    case ShaderDataType::Int:
        return sizeof(int);
    case ShaderDataType::Int2:
        return 2 * sizeof(int);
    case ShaderDataType::Int3:
        return 3 * sizeof(int);
    case ShaderDataType::Int4:
        return 4 * sizeof(int);
    default:
        break;
    }

    GE_ASSERT(false, "Unreachable Code");
}
GLenum ShaderDataTypeToGLtype(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:
    case ShaderDataType::Float2:
    case ShaderDataType::Float3:
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
    case ShaderDataType::Int2:
    case ShaderDataType::Int3:
    case ShaderDataType::Int4:
        return GL_INT;
    default:
        break;
    }

    GE_ASSERT(false, "Unreachable Code");
}

Sptr<VertexBuffer> VertexBuffer::create(float* vertices, std::size_t size)
{
    return Sptr<VertexBuffer>{new GLVertexBuffer{vertices, size}};
}

Sptr<IndexBuffer> IndexBuffer::create(std::uint32_t* indices, std::uint32_t count)
{
    return Sptr<IndexBuffer>{new GLIndexBuffer{indices, count}};
}

}