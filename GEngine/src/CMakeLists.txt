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

        graphics/Window.cc graphics/Window.hh
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
        glfw
        glad
)

target_include_directories(
    ge
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(
    ge
    PRIVATE
        GE_BUILD_DLL
    PUBLIC
        $<$<CONFIG:Debug>:GE_DEBUG>
)