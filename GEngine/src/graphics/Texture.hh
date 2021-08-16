#pragma once

#include <common.hh>
#include <string_view>

namespace GE
{
class GE_PUBLIC Texture
{

public:
    virtual ~Texture() = default;

    virtual std::uint32_t getWidth() const = 0;
    virtual std::uint32_t getHeight() const = 0;
    virtual void bind(std::uint32_t slot) = 0;
};

class GE_PUBLIC Texture2D : public Texture
{
public:
    static Sptr<Texture2D> create(std::string_view filePath);
};
}