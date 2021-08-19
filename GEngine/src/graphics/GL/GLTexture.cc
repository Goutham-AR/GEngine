#include "GLTexture.hh"
#include <utils/Logger.hh>

#include <stb_image/stb_image.h>

namespace GE
{

GLTexture2D::GLTexture2D(uint32_t width, uint32_t height)
    : m_width{width},
      m_height{height}
{
    m_internalFormat = GL_RGBA8, m_dataFormat = GL_RGBA;

    GE_ASSERT(m_internalFormat && m_dataFormat, "Texture Format Not Supported");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
    glTextureStorage2D(m_handle, 1, m_internalFormat, m_width, m_height);
    glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

GLTexture2D::GLTexture2D(std::string_view filePath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    auto data = stbi_load(filePath.data(), &width, &height, &channels, 0);
    GE_ASSERT(data, "Failed to load texture");
    m_width = width;
    m_height = height;

    if (channels == 4)
    {
        m_internalFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        m_internalFormat = GL_RGB8;
        m_dataFormat = GL_RGB;
    }

    GE_ASSERT(m_internalFormat && m_dataFormat, "Texture Format Not Supported");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
    glTextureStorage2D(m_handle, 1, m_internalFormat, m_width, m_height);
    glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

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

void GLTexture2D::unbind(std::uint32_t slot)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GLTexture2D::setData(void* data, size_t size)
{
    glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
}

}