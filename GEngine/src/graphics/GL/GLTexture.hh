#pragma once

#include <common.hh>
#include "../Common/Texture.hh"

#include <glad/glad.h>

namespace GE
{
class GE_PUBLIC GLTexture2D : public Texture2D
{

public:
    GLTexture2D(std::string_view filePath);
    GLTexture2D(uint32_t width, uint32_t height);
    ~GLTexture2D() override;

    [[nodiscard]] std::uint32_t getWidth() const override { return m_width; }
    [[nodiscard]] std::uint32_t getHeight() const override { return m_height; }
    void bind(std::uint32_t slot) override;
    void unbind(std::uint32_t slot) override;
    void setData(void* data, size_t size) override;

    static GLTexture2D* createWhiteTexture(uint32_t width, uint32_t height)
    {
        auto whiteTexture = new GLTexture2D{width, height};
        uint32_t whiteTextureData = 0xffffffff;
        whiteTexture->setData(&whiteTextureData, sizeof(std::uint32_t));

        return whiteTexture;
    }

private:
    std::uint32_t m_width{};
    std::uint32_t m_height{};
    unsigned int m_handle{};
    GLenum m_dataFormat;
    GLenum m_internalFormat;
};
}