#pragma once

#include <string_view>
#include <string>

#include <geMath.hh>

namespace GE::core
{

class Shader
{
public:
    Shader() = default;
    ~Shader();
    Shader(std::string_view vertexPath, std::string_view fragmentPath);

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void bind() const;
    void unBind() const;

    void setUniform(std::string_view name, float value) const;
    void setUniform(std::string_view name, int value) const;

    void setUniform(std::string_view name, const math::vec2& vec) const;
    void setUniform(std::string_view name, const math::vec3& vec) const;
    void setUniform(std::string_view name, const math::vec4& vec) const;

    void setUniform(std::string_view name, const math::Mat4& mat) const;

    // for debugging only
    [[nodiscard]] const std::string& getVertexPath() const
    {
        return m_vertexPath;
    }
    [[nodiscard]] const std::string& getFragmentPath() const { return m_fragmentPath; }

    [[nodiscard]] unsigned int getHandle() const;

private:
    unsigned int m_handle{};

    // for debugging only
    std::string m_vertexPath{};
    std::string m_fragmentPath{};

    unsigned int load();
    [[nodiscard]] int getUniformLocation(std::string_view name) const;

    static std::string loadFromFile(std::string_view filePath);
};

}