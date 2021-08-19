#include "Texture.hh"

#include "../GL/GLTexture.hh"

namespace GE
{
Sptr<Texture2D> Texture2D::create(std::string_view filePath)
{
    return Sptr<Texture2D>{new GLTexture2D{filePath}};
}

Sptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
{
    return Sptr<Texture2D>{new GLTexture2D{width, height}};
}

}