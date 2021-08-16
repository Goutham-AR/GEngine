#pragma once

#include <common.hh>
#include "../Texture.hh"

namespace GE
{
class GE_PUBLIC GLTexture2D : public Texture2D
{

public:
    GLTexture2D(std::string_view filePath);
    ~GLTexture2D() override;

    [[nodiscard]] std::uint32_t getWidth() const override { return m_width; }
    [[nodiscard]] std::uint32_t getHeight() const override { return m_height; }
    void bind(std::uint32_t slot = 0) override;

private:
    std::uint32_t m_width{};
    std::uint32_t m_height{};
    unsigned int m_handle{};
};
}