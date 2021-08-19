#pragma once

#include <common.hh>
#include <string_view>

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
};

class GE_PUBLIC Texture2D : public Texture
{
public:
    static Sptr<Texture2D> create(std::string_view filePath);
    static Sptr<Texture2D> create(uint32_t width, uint32_t height);
};
}