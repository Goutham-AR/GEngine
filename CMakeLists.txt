cmake_minimum_required(VERSION 3.19)


project(
    GEngine
    DESCRIPTION "A Game Engine"
    LANGUAGES C CXX
    VERSION 0.1.0
)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

# prevent in-source build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR “In-source build detected!”)
endif()



if(WIN32)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()


# if(MSVC)
#     add_compile_options(/W3 /WX)
# else()
#     add_compile_options(-W -Wall -Werror)
# endif()

add_subdirectory(GEngine)


add_subdirectory(testApp)