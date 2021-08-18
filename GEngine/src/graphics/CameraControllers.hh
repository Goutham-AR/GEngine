#pragma once

#include <common.hh>
#include "Cameras.hh"
#include <Time.hh>
#include <events/AppEvent.hh>
#include <events/MouseEvent.hh>

namespace GE
{

class GE_PUBLIC OrthoCameraController
{
public:
    explicit OrthoCameraController(float aspectRatio);
    void onUpdate(TimeStep deltaTime);
    void onEvent(Event& e);
    [[nodiscard]] const auto& getCamera() const { return m_camera; }

private:
    float m_aspectRatio;
    float m_zoomLevel = 1.0f;
    OrthoGraphicCamera m_camera;
    float m_cameraTranslationSpeed = 1.0f;
    float m_cameraRotationSpeed = 1.0f;
};

}