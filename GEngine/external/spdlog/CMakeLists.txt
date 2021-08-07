add_library(
    spdlog
    STATIC
    IMPORTED
    GLOBAL
)


target_include_directories(
    spdlog
    INTERFACE
        include
)

if(WIN32)
set_property(
    TARGET spdlog
    PROPERTY
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/spdlogd.lib"
)
endif()