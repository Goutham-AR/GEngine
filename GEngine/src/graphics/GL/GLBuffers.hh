#pragma once

#include <common.hh>
#include "../Common/Buffers.hh"

namespace GE
{

// -------------------------------------------------------
// ------------------- VertexBuffer -----------------------
// -------------------------------------------------------
class GE_PUBLIC GLVertexBuffer : public VertexBuffer
{
public:
    GLVertexBuffer(float* vertices, std::size_t size);
    GLVertexBuffer(std::size_t size);
    ~GLVertexBuffer() override;

    void bind() const override;
    void unbind() const override;

    void setData(const void* data, std::size_t size) override;

    void setLayout(BufferLayout& layout) override;
    const BufferLayout& getLayout() const override;

private:
    unsigned int m_handle{};
    BufferLayout m_layout{};
};

// -------------------------------------------------------
// ------------------- IndexBuffer -----------------------
// -------------------------------------------------------
class GE_PUBLIC GLIndexBuffer : public IndexBuffer
{
public:
    GLIndexBuffer(std::uint32_t* indices, std::uint32_t count);
    ~GLIndexBuffer() override;

    void bind() const override;
    void unbind() const override;

    std::uint32_t getCount() const override;

private:
    unsigned int m_handle{};
    std::uint32_t m_count;
};

}