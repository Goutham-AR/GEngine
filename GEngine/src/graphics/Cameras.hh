#pragma once

#include <common.hh>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GE
{

class GE_PUBLIC OrthoGraphicCamera
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

    // void setProjectionMat(const glm::mat4& projMat) { m_projMat = projMat; }
    // void setViewMat(const glm::mat4& viewMat) { m_viewMat = viewMat; }
    // void setViewProjectionMat(const glm::mat4& vpMat) { m_vpMat = vpMat; }
    void setPosition(const glm::vec3& pos)
    {
        m_pos = pos;
        calcViewMat();
    }
    void setRotation(float rotation)
    {
        m_rotation = rotation;
        calcViewMat();
    }

    [[nodiscard]] const auto& getProjectionMat() const { return m_projMat; }
    [[nodiscard]] const auto& getViewMat() const { return m_viewMat; }
    [[nodiscard]] const auto& getViewProjectionMat() const { return m_vpMat; }
    [[nodiscard]] const auto& getPosition() const { return m_pos; }
    [[nodiscard]] auto getRotation() const { return m_rotation; }

private:
    glm::mat4 m_projMat;
    glm::mat4 m_viewMat;
    glm::mat4 m_vpMat;

    glm::vec3 m_pos;
    float m_rotation = 0.0f;

private:
    void calcViewMat()
    {
        auto transformMat = glm::translate(glm::mat4{1.0f}, m_pos);
        transformMat = glm::rotate(transformMat, glm::radians(m_rotation), glm::vec3{0, 0, 1});

        m_viewMat = glm::inverse(transformMat);
        m_vpMat = m_projMat * m_viewMat;
    }
};
}