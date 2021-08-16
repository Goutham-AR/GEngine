#pragma once

#include <common.hh>
#include <utils/Logger.hh>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <initializer_list>
#include <string>

#include <glad/glad.h>

namespace GE
{

enum class ShaderDataType
{
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4
};

// name and accessibility should be changed
GE_PUBLIC std::uint32_t ShaderDataTypeSize(ShaderDataType type);
GE_PUBLIC GLenum ShaderDataTypeToGLtype(ShaderDataType type);

struct GE_PUBLIC BufferElement
{
    BufferElement(ShaderDataType type_, std::string_view name_, bool isNormalized_)
        : type{type_},
          name{name_},
          size{ShaderDataTypeSize(type_)},
          offset{},
          isNormalized{isNormalized_}
    {
    }

    [[nodiscard]] std::uint32_t getPerVertexCount() const
    {
        switch (type)
        {
        case ShaderDataType::Float:
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Float2:
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Float3:
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Float4:
        case ShaderDataType::Int4:
            return 4;

        case ShaderDataType::Mat3:
            return 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4;
        default:
            break;
        }

        GE_ASSERT(false, "Unreachable Code");
    }

    std::string name;
    ShaderDataType type;
    std::uint32_t size{};
    std::size_t offset{};
    bool isNormalized;
};

class GE_PUBLIC BufferLayout
{
public:
    BufferLayout(std::initializer_list<BufferElement> elements)
        : m_elements{elements}
    {
        std::size_t offset = 0;
        for (auto& elem : m_elements)
        {
            elem.offset = offset;
            offset += elem.size;
        }
        m_stride = offset;
    }

    [[nodiscard]] const std::vector<BufferElement>& getElements() const
    {
        return m_elements;
    }

    [[nodiscard]] std::uint32_t getStride() const { return m_stride; }

    [[nodiscard]] auto begin() const { return m_elements.begin(); }
    [[nodiscard]] auto end() const { return m_elements.end(); }

private:
    std::vector<BufferElement> m_elements;
    std::uint32_t m_stride;
};

// --------------------------------------------------------------------
// --------------------- VertexBuffer interface -----------------------
// --------------------------------------------------------------------
class GE_PUBLIC VertexBuffer
{
public:
    VertexBuffer() = default;
    virtual ~VertexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setLayout(BufferLayout& layout) = 0;
    [[nodiscard]] virtual const BufferLayout& getLayout() const = 0;

    static VertexBuffer* create(float* vertices, std::size_t size);
};

// --------------------------------------------------------------------
// --------------------- IndexBuffer interface -----------------------
// --------------------------------------------------------------------
class GE_PUBLIC IndexBuffer
{
public:
    IndexBuffer() = default;
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    [[nodiscard]] virtual std::uint32_t getCount() const = 0;

    static IndexBuffer* create(std::uint32_t* indices, std::uint32_t count);
};
}