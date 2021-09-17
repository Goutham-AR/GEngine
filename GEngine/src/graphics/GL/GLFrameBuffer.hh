#pragma once

#include "../Renderer/FrameBuffer.hh"

namespace GE
{
class GLFrameBuffer : public FrameBuffer
{
public:
    explicit GLFrameBuffer(const FrameBufferSpec& spec);

    ~GLFrameBuffer() override;

    void invalidate();

    void bind() override;
    void unbind() override;
    unsigned int getColorAttachment() const override
    {
        return m_colorAttachment;
    }

    [[nodiscard]] const FrameBufferSpec& getSpec() const override
    {
        return m_spec;
    }

private:
    FrameBufferSpec m_spec;
    unsigned int m_handle{};
    unsigned int m_colorAttachment{};
    unsigned int m_depthAttachment{};
};
}