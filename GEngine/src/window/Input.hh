#pragma once

#include <utility>

#include "common.hh"
#include "KeyCode.hh"

namespace GE
{

// static class
class GE_PUBLIC Input
{
public:
    Input() = delete;
    ~Input() = delete;

    static bool isKeyPressed(KeyCode keyCode);
    static bool isMouseButtonPressed(MouseKey button);
    static std::pair<float, float> getMousePos();
    static float getMousePosX() { return getMousePos().first; }
    static float getMousePosY() { return getMousePos().second; }
};

}