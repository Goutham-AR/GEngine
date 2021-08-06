add_library(
    geGraphics

    Window.cc Window.hh
    Shader.cc Shader.hh
    VertexBuffer.cc VertexBuffer.hh
    IndexBuffer.cc IndexBuffer.hh
    VertexArray.cc VertexArray.hh

    Renderer2D.hh
    Simple2DRenderer.cc Simple2DRenderer.hh 
    Renderable2D.hh
)


target_link_libraries(
    geGraphics
    PUBLIC
        glfw
        glad
        geUtils
        geMath
)

target_include_directories(
    geGraphics
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
