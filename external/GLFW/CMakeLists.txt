# TODO: Make glfw a submodule

add_library(
    glfw
    STATIC
    IMPORTED
    GLOBAL
)

target_include_directories(
    glfw
    INTERFACE
        include
)

if (WIN32)

set_property(
    TARGET glfw
    PROPERTY
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"
)
else()

set_property(
    TARGET glfw
    PROPERTY
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a"
)

endif()

