#include "Shader.hh"
#include <utils/Logger.hh>
#include "../GL/GLShader.hh"

namespace GE
{
Sptr<IShader> IShader::create(std::string_view vertexPath, std::string_view fragmentPath)
{
    return Sptr<IShader>{new GLShader{vertexPath, fragmentPath}};
}

void ShaderLibrary::addShader(const Sptr<IShader>& shader)
{
    auto& name = shader->getShaderFileName();
    GE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader already Exist");
    m_shaders.insert({shader->getShaderFileName(), shader});
}
Sptr<IShader> ShaderLibrary::getShader(const std::string& name)
{
    GE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader does not Exist");
    return m_shaders.at(name);
}

void ShaderLibrary::load(std::string_view vertexPath, std::string_view fragmentPath)
{
    auto shader = IShader::create(vertexPath, fragmentPath);
    addShader(shader);
}

}