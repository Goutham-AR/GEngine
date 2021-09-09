#pragma once

#include <common.hh>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE
{

class GE_PUBLIC Camera
{
public:
    Camera() = default;
    virtual ~Camera() = default;

    virtual const glm::mat4& getViewProjectionMat() const = 0;
};

class GE_PUBLIC OrthoGraphicCamera : public Camera
{
public:
    OrthoGraphicCamera(float left, float right, float bottom, float top);

    void setProjection(float left, float right, float bottom, float top)
    {
        m_projMat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_vpMat = m_projMat * m_viewMat;
    }
    OrthoGraphicCamera(const OrthoGraphicCamera&) = default;
    OrthoGraphicCamera& operator=(const OrthoGraphicCamera&) = default;

    void setPosition(const glm::vec3& pos)
    {
        m_pos = pos;
        m_isDirty = true;
    }
    void setRotation(float rotation)
    {
        m_rotation = rotation;
        m_isDirty = true;
    }

    [[nodiscard]] const auto& getProjectionMat() const
    {
        return m_projMat;
    }
    [[nodiscard]] const auto& getViewMat() const
    {
        if (m_isDirty)
        {
            calcViewMat();
            m_isDirty = false;
        }
        return m_viewMat;
    }
    [[nodiscard]] const glm::mat4& getViewProjectionMat() const override
    {
        if (m_isDirty)
        {
            calcViewMat();
            m_isDirty = false;
        }
        return m_vpMat;
    }
    [[nodiscard]] const auto& getPosition() const { return m_pos; }
    [[nodiscard]] auto getRotation() const { return m_rotation; }

private:
    glm::mat4 m_projMat;
    mutable glm::mat4 m_viewMat;
    mutable glm::mat4 m_vpMat;
    glm::vec3 m_pos;
    float m_rotation = 0.0f;

    mutable bool m_isDirty = false;

private:
    void calcViewMat() const
    {
        auto transformMat = glm::translate(glm::mat4{1.0f}, m_pos);
        transformMat = glm::rotate(transformMat, glm::radians(m_rotation), glm::vec3{0, 0, 1});

        m_viewMat = glm::inverse(transformMat);
        m_vpMat = m_projMat * m_viewMat;
    }
};

class GE_PUBLIC PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fov, float aspectRatio, float near, float far)
        : m_fov{fov},
          m_aspectRatio{aspectRatio},
          m_near{near},
          m_far{far},
          m_proj{glm::perspective(m_fov, m_aspectRatio, m_near, m_far)},
          m_view{1.0f}
    {
        m_view = m_proj * m_view;
    }

    [[nodiscard]] const glm::mat4& getViewProjectionMat() const override
    {
        return m_viewProj;
    }

    void rotate(float angle)
    {
    }

    void move(const glm::vec3& newPos)
    {
    }

private:
    glm::vec3 m_pos{};
    glm::vec3 m_right = {1, 0, 0};
    glm::vec3 m_up = {0, 1, 0};
    glm::vec3 m_look = {0, 0, 1};

    float m_fov{};
    float m_aspectRatio{};
    float m_near{};
    float m_far{};

    glm::mat4 m_proj{};
    glm::mat4 m_view{};
    glm::mat4 m_viewProj{};

    bool m_isDirty = false;

private:
    void calcViewProj()
    {
        m_viewProj = m_proj * m_view;
    }
};

}