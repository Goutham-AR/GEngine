#include "Input.hh"

#include <GLFW/glfw3.h>
#include "App.hh"

namespace GE
{

bool Input::isKeyPressed(KeyCode keyCode)
{
    auto winHandle = App::get().getWindow().getWinHandle();
    auto glfwCode = static_cast<int>(keyCode);
    auto status = glfwGetKey(winHandle, glfwCode);
    return status == GLFW_PRESS ? true : false;
}

bool Input::isMouseButtonPressed(MouseKey button)
{
    auto winHandle = App::get().getWindow().getWinHandle();
    auto status = glfwGetMouseButton(winHandle, toGLFW(button));
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