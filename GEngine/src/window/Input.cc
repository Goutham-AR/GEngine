#include "Input.hh"

#include <GLFW/glfw3.h>
#include "App.hh"

namespace GE
{

bool Input::isKeyPressed(int keyCode)
{
    auto winHandle = App::get().getWindow().getWinHandle();
    auto status = glfwGetKey(winHandle, keyCode);
    return status == GLFW_PRESS ? true : false;
}

bool Input::isMouseButtonPressed(int button)
{
    auto winHandle = App::get().getWindow().getWinHandle();
    auto status = glfwGetMouseButton(winHandle, button);
    return status == GLFW_PRESS ? true : false;
}
std::pair<float, float> Input::getMousePos()
{
    auto winHandle = App::get().getWindow().getWinHandle();
    double xPos, yPos;
    glfwGetCursorPos(winHandle, &xPos, &yPos);
    return {
        static_cast<float>(xPos),
        static_cast<float>(yPos)};
}

}