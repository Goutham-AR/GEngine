#pragma once

#include <glad/glad.h>

#include <geMath.hh>

#include "VertexBuffer.hh"
#include "IndexBuffer.hh"
#include "Shader.hh"
#include "VertexArray.hh"

namespace GE::core
{

class Renderable2D
{

public:
    [[nodiscard]] inline const math::vec3& getPosition() const { return m_position; }
    [[nodiscard]] inline const math::vec2& getsize() const { return m_size; }
    [[nodiscard]] inline const math::vec4& getColor() const { return m_color; }

    [[nodiscard]] inline const VertexArray* getVAO() const { return m_vao; }
    [[nodiscard]] inline const IndexBuffer* getIBO() const { return m_ibo; }
    [[nodiscard]] inline Shader& getShader() const { return m_shader; }

    Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color, Shader& shader)
        : m_position{position},
          m_size{size},
          m_color{color},
          m_shader{shader}
    {
        m_vao = new VertexArray{};

        float vertices[] = {
            0, 0, 0,
            0, m_size.y(), 0,
            m_size.x(), m_size.y(), 0,
            m_size.x(), 0, 0};

        float colors[] = {
            m_color.x(), m_color.y(), m_color.z(), m_color.w(),
            m_color.x(), m_color.y(), m_color.z(), m_color.w(),
            m_color.x(), m_color.y(), m_color.z(), m_color.w(),
            m_color.x(), m_color.y(), m_color.z(), m_color.w()};

        m_vao->addBuffer(new VertexBuffer{vertices, 4 * 3, 3}, 0);
        m_vao->addBuffer(new VertexBuffer{colors, 4 * 4, 4}, 1);

        std::uint16_t indices[] = {
            0, 1, 2,
            2, 3, 0};

        m_ibo = new IndexBuffer{indices, 6};
    }
    virtual ~Renderable2D()
    {
        delete m_ibo;
        delete m_vao;
    }

private:
    math::vec3 m_position;
    math::vec2 m_size;
    math::vec4 m_color;

    Shader& m_shader;
    VertexArray* m_vao;
    IndexBuffer* m_ibo;
};

}