add_library(
    geMath
    INTERFACE
)

target_include_directories(
    geMath
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(UNIX AND NOT APPLE)
    target_link_libraries(
        geMath
        INTERFACE
            m
    )
endif()