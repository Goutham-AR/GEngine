#pragma once

#include "common.hh"

namespace GE
{

struct FrameBufferSpec
{
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t samples = 1;
    bool swapchainTarget = false;
};

class FrameBuffer
{
public:
    virtual ~FrameBuffer() = default;
    [[nodiscard]] virtual const FrameBufferSpec& getSpec() const = 0;
    // [[nodiscard]] virtual FrameBufferSpec& getSpec() = 0;
    virtual unsigned int getColorAttachment() const = 0;
    virtual void bind() = 0;
    virtual void unbind() = 0;
    static Sptr<FrameBuffer> create(const FrameBufferSpec& spec);

private:
};
}