#pragma once

#include <cstdint>
#include <cstddef>

namespace GE::core
{

class IndexBuffer
{

public:
    IndexBuffer(std::uint16_t* data, size_t count);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    void bind() const;
    void unBind() const;

    [[nodiscard]] size_t getCount() const { return m_count; }

private:
    unsigned int m_handle;
    size_t m_count;
};

}