#pragma once

#include <common.hh>

#include <string_view>
#include <string>

#include "../Shader.hh"

namespace GE
{
class GE_PUBLIC GLShader : public IShader
{

public:
    GLShader(std::string_view vertexPath, std::string_view fragmentPath);
    ~GLShader() override;

    void bind() const override;
    void unbind() const override;
    [[nodiscard]] const std::string& getShaderFileName() const override { return m_fileName; }
    void setUniform(std::string_view name, const glm::mat4& mat);
    void setUniform(std::string_view name, const glm::vec4& vec);
    void setUniform(std::string_view name, const glm::vec3& vec);
    void setUniform(std::string_view name, int val);

private:
    unsigned int m_handle{};
    std::string m_fileName;
    [[nodiscard]] int getUniformLocation(std::string_view name) const;
};

}