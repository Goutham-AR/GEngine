#pragma once

#include <common.hh>
#include <string_view>
#include <glm/glm.hpp>
#include <unordered_map>

namespace GE
{

class GE_PUBLIC IShader
{
public:
    virtual ~IShader() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    [[nodiscard]] virtual const std::string& getShaderFileName() const = 0;

    static Sptr<IShader> create(std::string_view vertexPath, std::string_view fragmentPath);
};

class GE_PUBLIC ShaderLibrary
{
public:
    void addShader(const Sptr<IShader>& shader);
    Sptr<IShader> getShader(const std::string& name);
    void load(std::string_view vertexPath, std::string_view fragmentPath);

private:
    std::unordered_map<std::string, Sptr<IShader>> m_shaders;
};

}