#pragma once

#include <common.hh>
#include "../VertexArray.hh"
#include "GLBuffers.hh"

namespace GE
{

class GE_PUBLIC GLVertexArray : public VertexArray
{
public:
    GLVertexArray();
    ~GLVertexArray() override;

    void bind() const override;
    void unbind() const override;

    void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;
    void addIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo) override;

    [[nodiscard]] const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override
    {
        return m_ibo;
    }
    [[nodiscard]] const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffer() const override
    {
        return m_vbos;
    }

private:
    unsigned int m_handle{};
    std::vector<std::shared_ptr<VertexBuffer>> m_vbos{};
    std::shared_ptr<IndexBuffer> m_ibo{};
};

}