#include "GLTexture.hh"
#include <utils/Logger.hh>

#include <glad/glad.h>
#include <stb_image/stb_image.h>

namespace GE
{

GLTexture2D::GLTexture2D(std::string_view filePath)
{
    int width, height, channels;
    auto data = stbi_load(filePath.data(), &width, &height, &channels, 0);
    GE_ASSERT(data, "Failed to load texture");

    m_width = width;
    m_height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
    glTextureStorage2D(m_handle, 1, GL_RGB8, m_width, m_height);
    glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

GLTexture2D::~GLTexture2D()
{
    glDeleteTextures(1, &m_handle);
}
void GLTexture2D::bind(std::uint32_t slot)
{
    glBindTextureUnit(slot, m_handle);
}

}