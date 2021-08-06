add_subdirectory(utils)
add_subdirectory(math)
add_subdirectory(core)

add_library(
    ge
    lib.cc
)

target_link_libraries(
    ge
    PUBLIC
        geCore
        geMath
        geUtils
)