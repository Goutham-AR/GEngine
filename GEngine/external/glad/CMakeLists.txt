add_library(
    glad
    src/glad.c
)

target_include_directories(
    glad
    PUBLIC
        include
)


if (UNIX AND NOT APPLE)
set_target_properties(glad PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()