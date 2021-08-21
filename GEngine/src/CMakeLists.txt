add_library(
    ge
    # SHARED
        App.cc    App.hh

        Time.hh
        common.hh geMain.hh
        GE.hh

        events/AppEvent.hh
        events/Event.hh
        events/KeyEvent.hh
        events/MouseEvent.hh

        window/Window.cc               window/Window.hh
        window/Input.cc                window/Input.hh
        window/KeyCode.hh

        layers/Layer.hh
        layers/LayerStack.cc           layers/LayerStack.hh
        layers/ImGui/ImGuiLayer.cc     layers/ImGui/ImGuiLayer.hh 
        layers/ImGui/ImGuiCore.cc

        graphics/Common/GraphicsContext.hh
        graphics/Common/Buffers.cc            graphics/Common/Buffers.hh
        graphics/Common/VertexArray.cc        graphics/Common/VertexArray.hh
        graphics/Common/Shader.cc             graphics/Common/Shader.hh
        graphics/Common/Renderer.cc           graphics/Common/Renderer.hh
        graphics/Common/Renderer2D.cc           graphics/Common/Renderer2D.hh
        graphics/Common/RendererAPI.cc        graphics/Common/RendererAPI.hh
        graphics/Common/RenderCommand.cc      graphics/Common/RenderCommand.hh
        graphics/Common/Cameras.cc            graphics/Common/Cameras.hh
        graphics/Common/CameraControllers.hh  graphics/Common/CameraControllers.cc
        graphics/Common/Texture.cc            graphics/Common/Texture.hh

        graphics/GL/GLContext.cc       graphics/GL/GLContext.hh
        graphics/GL/GLShader.cc        graphics/GL/GLShader.hh
        graphics/GL/GLBuffers.cc       graphics/GL/GLBuffers.hh
        graphics/GL/GLVertexArray.cc   graphics/GL/GLVertexArray.hh
        graphics/GL/GLRendererAPI.cc   graphics/GL/GLRendererAPI.hh
        graphics/GL/GLTexture.cc       graphics/GL/GLTexture.hh

        utils/FileIO.cc               utils/FileIO.hh
        utils/Logger.cc utils/Logger.hh      utils/Instrumentor.hh


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
        imGui
        glfw
        glad
        glm
        spdlog
        stb_image
        
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
        # GE_BUILD_DLL
)
