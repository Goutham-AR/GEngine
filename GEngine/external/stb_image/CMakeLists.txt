add_library(
    stb_image
    src/stb_image.c
    include/stb_image/stb_image.h
)

target_include_directories(
    stb_image
    PUBLIC
        include
)