add_executable(
    testApp2D
    src/main.cc
    src/TestLayer.cc
    src/TestLayer.hh
)

target_link_libraries(
    testApp2D
    PRIVATE
        ge
)

set_property(
    TARGET testApp2D
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
