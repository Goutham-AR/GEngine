#pragma once

#include <utility>

#include "common.hh"
#include "KeyCode.hh"

namespace GE
{

// static class
class Input
{
public:
    Input() = delete;
    ~Input() = delete;

    static bool isKeyPressed(KeyCode keyCode);
    static bool isMouseButtonPressed(int button);
    static std::pair<float, float> getMousePos();
    static float getMousePosX() { return getMousePos().first; }
    static float getMousePosY() { return getMousePos().second; }
};

}