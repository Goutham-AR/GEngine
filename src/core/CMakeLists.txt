add_subdirectory(graphics)

add_library(
    geCore
    geCore.cc
)


target_link_libraries(
    geCore
    PUBLIC
        geGraphics
)

if(UNIX AND NOT APPLE)
target_link_libraries(
    geCore
    PUBLIC
        dl
        pthread
        GL
)
endif()