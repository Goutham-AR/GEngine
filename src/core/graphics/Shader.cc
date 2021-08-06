#include "Shader.hh"

#include <glad/glad.h>

#include <iostream>

#include <utils.hh>

namespace GE::core
{

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
    : m_vertexPath{vertexPath},
      m_fragmentPath{fragmentPath}
{
    m_handle = load();
}

Shader::~Shader()
{
    glDeleteProgram(m_handle);
}

void Shader::bind() const
{
    glUseProgram(m_handle);
}

void Shader::unBind() const
{
    glUseProgram(0);
}

unsigned int Shader::getHandle() const
{
    return m_handle;
}

void Shader::setUniform(std::string_view name, float value) const
{
    glUniform1f(getUniformLocation(name), value);
}
void Shader::setUniform(std::string_view name, int value) const
{
    glUniform1i(getUniformLocation(name), value);
}
void Shader::setUniform(std::string_view name, const math::vec2& vec) const
{
    glUniform2fv(getUniformLocation(name), 1, vec.elements);
}
void Shader::setUniform(std::string_view name, const math::vec3& vec) const
{
    glUniform3fv(getUniformLocation(name), 1, vec.elements);
}
void Shader::setUniform(std::string_view name, const math::vec4& vec) const
{
    glUniform4fv(getUniformLocation(name), 1, vec.elements);
}
void Shader::setUniform(std::string_view name, const math::Mat4& mat) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat.at(0, 0));
}

std::string Shader::loadFromFile(std::string_view filePath)
{
    return GE::utils::read_file(filePath);
}

unsigned int Shader::load()
{
    auto program = glCreateProgram();

    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    auto vertexSrc = loadFromFile(m_vertexPath);
    auto fragmentSrc = loadFromFile(m_fragmentPath);

    auto vcstr = vertexSrc.c_str();
    auto fcstr = fragmentSrc.c_str();

    glShaderSource(vertexShader, 1, &vcstr, nullptr);
    glCompileShader(vertexShader);
    // TODOS: Error handling
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex Shader Compilation Failed\n"
                  << infoLog << std::endl;
        glDeleteShader(vertexShader);
        return 0;
    }

    glShaderSource(fragmentShader, 1, &fcstr, nullptr);
    glCompileShader(fragmentShader);
    // TODOS: Error handling
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: Vertex Shader Compilation Failed\n"
                  << infoLog << std::endl;
        glDeleteShader(fragmentShader);
        return 0;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    // TODOS: Error handling
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader Program Linking Failed\n"
                  << infoLog << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

int Shader::getUniformLocation(std::string_view name) const
{
    return glGetUniformLocation(m_handle, name.data());
}

}