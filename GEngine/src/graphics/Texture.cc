#include "Texture.hh"

#include "GL/GLTexture.hh"

namespace GE
{
Sptr<Texture2D> Texture2D::create(std::string_view filePath)
{
    return Sptr<Texture2D>{new GLTexture2D{filePath}};
}
}