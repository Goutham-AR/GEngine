add_executable(
    test_app
    src/main.cc
)

target_link_libraries(
    test_app
    PRIVATE
        ge
)