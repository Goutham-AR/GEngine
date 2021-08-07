add_executable(
    testApp
    src/main.cc
)

target_link_libraries(
    testApp
    PRIVATE
        ge
)

set_target_properties(
    testApp
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/bin
)
