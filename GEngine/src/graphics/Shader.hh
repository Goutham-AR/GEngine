#pragma once

#include <common.hh>
#include <string_view>
#include <glm/glm.hpp>

namespace GE
{

class GE_PUBLIC Shader
{
public:
    virtual ~Shader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setUniform(std::string_view name, const glm::mat4& mat) = 0;

    static Shader* create(std::string_view vertexPath, std::string_view fragmentPath);
};

}