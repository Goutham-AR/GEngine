add_executable(
    testApp3D
    src/main.cc
    src/TestLayer.cc
    src/TestLayer.hh
)

target_link_libraries(
    testApp3D
    PRIVATE
        ge
)

set_target_properties(
    testApp3D
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
            ${CMAKE_BINARY_DIR}/bin
)

set_property(
    TARGET testApp3D
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
