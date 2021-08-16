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

    void addVertexBuffer(const Sptr<VertexBuffer>& vbo) override;
    void addIndexBuffer(const Sptr<IndexBuffer>& ibo) override;

    [[nodiscard]] const Sptr<IndexBuffer>& getIndexBuffer() const override
    {
        return m_ibo;
    }
    [[nodiscard]] const std::vector<Sptr<VertexBuffer>>& getVertexBuffer() const override
    {
        return m_vbos;
    }

private:
    unsigned int m_handle{};
    std::vector<Sptr<VertexBuffer>> m_vbos{};
    Sptr<IndexBuffer> m_ibo{};
};

}