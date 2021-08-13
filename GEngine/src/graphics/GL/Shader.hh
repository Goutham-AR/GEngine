#pragma once

#include <common.hh>

#include <string_view>
#include <string>

namespace GE
{
class GE_PUBLIC Shader
{

public:
    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

private:
    std::string readFromFile(std::string_view filePath);

private:
    unsigned int m_handle{};
};



}