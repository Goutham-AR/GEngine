#include "Shader.hh"

#include "GL/GLShader.hh"

namespace GE
{
Shader* Shader::create(std::string_view vertexPath, std::string_view fragmentPath)
{
    return new GLShader{vertexPath, fragmentPath};
}




}