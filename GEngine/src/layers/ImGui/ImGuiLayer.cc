#include "ImGuiLayer.hh"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App.hh"
#include "events/Event.hh"
#include "events/MouseEvent.hh"
#include "events/KeyEvent.hh"
#include "events/AppEvent.hh"

#include "ImGuiOpenglRenderer.h"

namespace GE
{

ImGuiLayer::ImGuiLayer()
    : Layer{"ImGuiLayer"}
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::onAttach()
{

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    auto& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 410");
}
void ImGuiLayer::onDetach()
{
}
void ImGuiLayer::onUpdate()
{
    auto& io = ImGui::GetIO();
    auto& app = App::get();

    io.DisplaySize = ImVec2(
        static_cast<float>(app.getWindow().getWidth()),
        static_cast<float>(app.getWindow().getheight()));

    auto time = static_cast<float>(glfwGetTime());
    io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void ImGuiLayer::onEvent(Event& event)
{
    EventDispatcher dispatcher{event};

    dispatcher.dispatchEvent<MouseButtonPressedEvent>(
        [this](MouseButtonPressedEvent& e) {
            auto& io = ImGui::GetIO();
            auto mouseCode = toGLFW(e.getMouseButton());
            io.MouseDown[mouseCode] = true;
            return false;
        });

    dispatcher.dispatchEvent<MouseButtonReleasedEvent>(
        [this](MouseButtonReleasedEvent& e) {
            auto& io = ImGui::GetIO();
            auto mouseCode = toGLFW(e.getMouseButton());
            io.MouseDown[mouseCode] = false;
            return false;
        });

    dispatcher.dispatchEvent<MouseScrolledEvent>(
        [this](MouseScrolledEvent& e) {
            auto& io = ImGui::GetIO();
            io.MouseWheelH += e.getXOffset();
            io.MouseWheel += e.getYOffset();

            return false;
        });

    dispatcher.dispatchEvent<MouseMovedEvent>(
        [this](MouseMovedEvent& e) {
            auto& io = ImGui::GetIO();
            io.MousePos = ImVec2(e.getX(), e.getY());
            return false;
        });
    dispatcher.dispatchEvent<KeyPressedEvent>(
        [this](KeyPressedEvent& e) {
            auto& io = ImGui::GetIO();
            auto keyCode = toGLFW(e.getKeyCode());
            io.KeysDown[keyCode] = true;

            io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
            io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
            io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
            io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

            return false;
        });

    dispatcher.dispatchEvent<KeyReleasedEvent>(
        [this](KeyReleasedEvent& e) {
            auto& io = ImGui::GetIO();
            auto keyCode = toGLFW(e.getKeyCode());
            io.KeysDown[keyCode] = false;
            return false;
        });

    dispatcher.dispatchEvent<KeyTypedEvent>(
        [this](KeyTypedEvent& e) {
            auto& io = ImGui::GetIO();
            auto keyCode = toGLFW(e.getKeyCode());
            if (keyCode > 0 && keyCode < 0x10000)
            {
                io.AddInputCharacter(keyCode);
            }
            return false;
        });

    dispatcher.dispatchEvent<WindowResizeEvent>(
        [this](WindowResizeEvent& e) {
            auto& io = ImGui::GetIO();
            io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
            io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

            glViewport(0, 0, e.getWidth(), e.getWidth());

            return false;
        });
}

}