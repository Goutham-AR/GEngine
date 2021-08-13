#pragma once

#include <common.hh>

#include <string_view>
#include <string>

#include "../Shader.hh"

namespace GE
{
class GE_PUBLIC GLShader : public Shader
{

public:
    GLShader(std::string_view vertexPath, std::string_view fragmentPath);
    ~GLShader() override;

    void bind() const override;
    void unbind() const override;

private:
    std::string readFromFile(std::string_view filePath);

private:
    unsigned int m_handle{};
};



}