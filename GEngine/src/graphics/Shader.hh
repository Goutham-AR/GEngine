#pragma once

#include <common.hh>
#include <string_view>

namespace GE
{

class GE_PUBLIC Shader
{
public:
    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static Shader* create(std::string_view vertexPath, std::string_view fragmentPath);





};




}