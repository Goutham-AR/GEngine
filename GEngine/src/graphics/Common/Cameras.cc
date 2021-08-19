#include "Cameras.hh"

namespace GE
{

OrthoGraphicCamera::OrthoGraphicCamera(float left, float right, float bottom, float top)
    : m_projMat{glm::ortho(left, right, bottom, top, -1.0f, 1.0f)},
      m_viewMat{1.0f},
      m_pos{0.0f}
{
    m_vpMat = m_projMat * m_viewMat;
}

}