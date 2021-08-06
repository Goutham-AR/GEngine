add_library(
    geMath
    INTERFACE
)

target_include_directories(
    geMath
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    geMath
    INTERFACE
        m
)