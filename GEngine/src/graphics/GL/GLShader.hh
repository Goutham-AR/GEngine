#pragma once

#include <common.hh>

#include <string_view>
#include <string>

#include "../Common/Shader.hh"

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
    void setUniform(std::string_view name, const glm::mat4& mat) override;
    void setUniform(std::string_view name, const glm::vec4& vec) override;
    void setUniform(std::string_view name, const glm::vec3& vec) override;
    void setUniform(std::string_view name, int val) override;
    void setUniform(std::string_view name, int* vals, std::size_t size) override;
    void setUniform(std::string_view name, float val) override;

private:
    unsigned int m_handle{};
    std::string m_fileName;
    [[nodiscard]] int getUniformLocation(std::string_view name) const;
};

}