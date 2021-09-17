#include "FrameBuffer.hh"
#include "../GL/GLFrameBuffer.hh"

namespace GE
{
Sptr<FrameBuffer> FrameBuffer::create(const FrameBufferSpec& spec)
{
    return std::make_shared<GLFrameBuffer>(spec);
}
}