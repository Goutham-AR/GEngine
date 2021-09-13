#pragma once

#include <common.hh>
#include <string_view>
#include <glm/glm.hpp>

namespace GE
{
class GE_PUBLIC Texture
{

public:
    virtual ~Texture() = default;

    [[nodiscard]] virtual std::uint32_t getWidth() const = 0;
    [[nodiscard]] virtual std::uint32_t getHeight() const = 0;
    virtual void bind(std::uint32_t slot) = 0;
    virtual void unbind(std::uint32_t slot) = 0;
    virtual void setData(void* data, size_t size) = 0;

    virtual unsigned int getHandle() const = 0;
};

class GE_PUBLIC Texture2D : public Texture
{
public:
    static Sptr<Texture2D> create(std::string_view filePath);
    static Sptr<Texture2D> create(uint32_t width, uint32_t height);
    static Sptr<Texture2D> createWhiteTexture(uint32_t width, uint32_t height);
};

struct GE_PUBLIC SubTexture2D
{
public:
    SubTexture2D(const glm::vec2& min, const glm::vec2& max)
    {
        m_subTexCoord[0] = {min.x, min.y};
        m_subTexCoord[1] = {max.x, min.y};
        m_subTexCoord[2] = {max.x, max.y};
        m_subTexCoord[3] = {min.x, max.y};
    }

    SubTexture2D()
    {
        m_subTexCoord[0] = {0, 0};
        m_subTexCoord[1] = {1, 0};
        m_subTexCoord[2] = {1, 1};
        m_subTexCoord[3] = {0, 1};
    }

    static Sptr<SubTexture2D> createFromCoords(const Sptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = {1, 1})
    {
        float sheetWidth = texture->getWidth();
        float sheetHeight = texture->getHeight();

        glm::vec2 min = {(coords.x * cellSize.x) / sheetWidth,
                         (coords.y * cellSize.y) / sheetHeight};
        glm::vec2 max = {((coords.x + spriteSize.x) * cellSize.x) / sheetWidth,
                         ((coords.y + spriteSize.y) * cellSize.y) / sheetHeight};

        return std::make_shared<SubTexture2D>(min, max);
    }

    static Sptr<SubTexture2D> create()
    {
        return std::make_shared<SubTexture2D>();
    }

    glm::vec2 m_subTexCoord[4]{};
};

}