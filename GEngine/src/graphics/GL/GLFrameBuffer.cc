#include "GLFrameBuffer.hh"

#include <glad/glad.h>

#include "utils/Logger.hh"

namespace GE
{
GLFrameBuffer::GLFrameBuffer(const FrameBufferSpec& spec)
    : m_spec{spec}
{
    invalidate();
}
GLFrameBuffer::~GLFrameBuffer()
{
    glDeleteFramebuffers(1, &m_handle);
}

void GLFrameBuffer::invalidate()
{
    glCreateFramebuffers(1, &m_handle);
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);

    // glGenTextures(1, &m_colorAttachment);
    // glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)m_spec.width, (GLsizei)m_spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    // glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glNamedFramebufferTexture(m_handle, GL_COLOR_ATTACHMENT0, m_colorAttachment, 0);

    glGenRenderbuffers(1, &m_colorAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, m_spec.width, m_spec.height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // glGenTextures(1, &m_depthAttachment);
    // glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_spec.width, m_spec.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    // // glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, (GLsizei)m_spec.width, (GLsizei)m_spec.height);
    // glNamedFramebufferTexture(m_handle, GL_DEPTH_STENCIL_ATTACHMENT, m_depthAttachment, 0);

    glGenRenderbuffers(1, &m_depthAttachment);
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthAttachment);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_STENCIL, m_spec.width, m_spec.height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorAttachment);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthAttachment);

    GE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "FrameBuffer is incomplete");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
}
void GLFrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}