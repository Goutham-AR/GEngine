#pragma once

#include <common.hh>
#include "../Buffers.hh"

namespace GE
{

class GE_PUBLIC GLVertexBuffer : public VertexBuffer
{
public:
    GLVertexBuffer(float* vertices, std::size_t size);
    ~GLVertexBuffer() override;


    void bind() const override;
    void unbind() const override;


private:
    unsigned int m_handle;

};


class GE_PUBLIC GLIndexBuffer : public IndexBuffer
{
public:
    GLIndexBuffer(std::uint32_t* indices, std::size_t size);
    ~GLIndexBuffer() override;

    void bind() const override;
    void unbind() const override;


private:
    unsigned int m_handle;


};


}