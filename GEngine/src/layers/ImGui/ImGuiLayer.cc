#include "ImGuiLayer.hh"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App.hh"
#include "Logger.hh"
#include "events/Event.hh"
#include "events/MouseEvent.hh"
#include "events/KeyEvent.hh"
#include "events/AppEvent.hh"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace GE
{

ImGuiLayer::ImGuiLayer()
    : Layer{"ImGuiLayer"}
{
}

void ImGuiLayer::onAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    auto& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    auto& app = App::get();
    auto winHandle = app.getWindow().getWinHandle();

    ImGui_ImplGlfw_InitForOpenGL(winHandle, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}
void ImGuiLayer::onDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void ImGuiLayer::onUpdate()
{
}

void ImGuiLayer::onImGuiRender()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}
void ImGuiLayer::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void ImGuiLayer::end()
{
    auto& io = ImGui::GetIO();

    auto& app = App::get();

    io.DisplaySize = ImVec2{
        static_cast<float>(app.getWindow().getWidth()),
        static_cast<float>(app.getWindow().getWidth())};

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        auto backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}

}