#include "GLShader.hh"

#include <vector>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include <utils/Logger.hh>
#include <glad/glad.h>
#include <utils/FileIO.hh>

namespace GE
{

GLShader::GLShader(std::string_view vertexPath, std::string_view fragmentPath)
{

    // Read our shaders into the appropriate buffers
    auto vertexSource = utils::FileIO::readText(vertexPath);
    auto fragmentSource = utils::FileIO::readText(fragmentPath);

    // Create an empty vertex shader handle
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    auto source = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        ENGINE_LOG_ERROR("ERROR:Vertex Shader Compilation Failed");
        ENGINE_LOG_ERROR("\t{0}", infoLog.data());

        // In this simple program, we'll just leave
        return;
    }

    // Create an empty fragment shader handle
    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        ENGINE_LOG_ERROR("ERROR:Fragment Shader Compilation Failed");
        ENGINE_LOG_ERROR("\t{0}", infoLog.data());

        // In this simple program, we'll just leave
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    m_handle = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(m_handle, vertexShader);
    glAttachShader(m_handle, fragmentShader);

    // Link our program
    glLinkProgram(m_handle);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_handle, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_handle, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(m_handle);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        ENGINE_LOG_ERROR("ERROR:Shader Program Linking Failed");
        ENGINE_LOG_ERROR("\t{0}", infoLog.data());

        // In this simple program, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(m_handle, vertexShader);
    glDetachShader(m_handle, fragmentShader);
}

GLShader::~GLShader()
{
    glDeleteProgram(m_handle);
}

void GLShader::bind() const
{
    glUseProgram(m_handle);
}

void GLShader::unbind() const
{
    glUseProgram(0);
}

void GLShader::setUniform(std::string_view name, const glm::mat4& mat)
{
    glProgramUniformMatrix4fv(m_handle, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void GLShader::setUniform(std::string_view name, const glm::vec4& vec)
{
    glProgramUniform4fv(m_handle, getUniformLocation(name), 1, glm::value_ptr(vec));
}
void GLShader::setUniform(std::string_view name, const glm::vec3& vec)
{
    glProgramUniform3fv(m_handle, getUniformLocation(name), 1, glm::value_ptr(vec));
}

int GLShader::getUniformLocation(std::string_view name) const
{
    return glGetUniformLocation(m_handle, name.data());
}

}