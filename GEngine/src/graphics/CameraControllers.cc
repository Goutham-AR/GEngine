#include "CameraControllers.hh"
#include <window/Input.hh>

namespace GE
{

OrthoCameraController::OrthoCameraController(float aspectRatio)
    : m_aspectRatio{aspectRatio},
      m_camera{-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel}
{
}
void OrthoCameraController::onUpdate(TimeStep deltaTime)
{

    auto inSeconds = deltaTime.getSeconds();

    if (Input::isKeyPressed(KeyCode::W) || Input::isKeyPressed(KeyCode::UpArrow))
    {

        m_camera.setPosition(
            glm::vec3{
                m_camera.getPosition().x,
                m_camera.getPosition().y - m_cameraTranslationSpeed * inSeconds,
                m_camera.getPosition().z});
    }
    else if (Input::isKeyPressed(KeyCode::S) || Input::isKeyPressed(KeyCode::DownArrow))
    {
        m_camera.setPosition(
            glm::vec3{
                m_camera.getPosition().x,
                m_camera.getPosition().y + m_cameraTranslationSpeed * inSeconds,
                m_camera.getPosition().z});
    }

    if (Input::isKeyPressed(KeyCode::A) || Input::isKeyPressed(KeyCode::LeftArrow))
    {
        m_camera.setPosition(
            glm::vec3{
                m_camera.getPosition().x + m_cameraTranslationSpeed * inSeconds,
                m_camera.getPosition().y,
                m_camera.getPosition().z});
    }

    else if (Input::isKeyPressed(KeyCode::D) || Input::isKeyPressed(KeyCode::RightArrow))
    {
        m_camera.setPosition(
            glm::vec3{
                m_camera.getPosition().x - m_cameraTranslationSpeed * inSeconds,
                m_camera.getPosition().y,
                m_camera.getPosition().z});
    }

    m_cameraTranslationSpeed = m_zoomLevel;
}
void OrthoCameraController::onEvent(Event& e)
{
    EventDispatcher dispatcher{e};

    dispatcher.dispatchEvent<MouseScrolledEvent>(
        [this](MouseScrolledEvent& event) -> bool
        {
            this->m_zoomLevel -= event.getYOffset() * 0.5f;
            m_zoomLevel = std::max(m_zoomLevel, 0.25f);
            m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
            return false;
        });

    dispatcher.dispatchEvent<WindowResizeEvent>(
        [this](WindowResizeEvent& event) -> bool
        {
            m_aspectRatio = static_cast<float>(event.getWidth()) / event.getHeight();
            m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
            return false;
        });
}

}
