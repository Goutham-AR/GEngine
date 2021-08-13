add_library(
    ge
    SHARED
        App.cc App.hh
        Logger.cc Logger.hh
        common.hh geMain.hh
        GE.hh

        events/AppEvent.hh
        events/Event.hh
        events/KeyEvent.hh
        events/MouseEvent.hh

        window/Window.cc      window/Window.hh
        window/Input.cc       window/Input.hh
        window/KeyCode.hh

        layers/Layer.hh
        layers/LayerStack.cc layers/LayerStack.hh

        layers/ImGui/ImGuiLayer.cc layers/ImGui/ImGuiLayer.hh 
        layers/ImGui/ImGuiCore.cc

        graphics/GraphicsContext.hh
        graphics/Buffers.cc graphics/Buffers.hh

        graphics/GL/GLContext.cc graphics/GL/GLContext.hh
        graphics/GL/GLShader.cc graphics/GL/GLShader.hh
        graphics/GL/GLBuffers.cc graphics/GL/GLBuffers.hh
)

set_target_properties(
    ge
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/bin
)
target_link_libraries(
    ge
    PUBLIC
        spdlog
        imGui
        glfw
        glad
        glm
        
)

target_include_directories(
    ge
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(
    ge
    PRIVATE
        GE_ENABLE_EXPORT
        
    PUBLIC
        $<$<CONFIG:Debug>:GE_DEBUG>
        GLFW_INCLUDE_NONE
        GE_BUILD_DLL
)
