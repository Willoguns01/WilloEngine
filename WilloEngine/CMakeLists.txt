# WilloEngine

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE WILLO_ENGINE_INCLUDE include/WilloEngine/*.hpp)
file(GLOB_RECURSE WILLO_ENGINE_SOURCE src/*.cpp)
file(GLOB_RECURSE WILLO_ENGINE_PRIVATE_INCLUDE src/*.hpp)

project(WilloEngine)
add_library(WilloEngine ${WILLO_ENGINE_SOURCE} ${WILLO_ENGINE_INCLUDE} ${WILLO_ENGINE_PRIVATE_INCLUDE})
target_include_directories(WilloEngine PUBLIC include/)
target_include_directories(WilloEngine PRIVATE src/)

find_package(SDL2 CONFIG REQUIRED)

target_link_Libraries(WilloEngine PRIVATE SDL2::SDL2 d3d11 dxgi)

option(WILLO_ENGINE_ENABLE_PROFILING "Enable profiling for WilloEngine" ON)

if (WILLO_ENGINE_ENABLE_PROFILING)
    target_link_libraries(WilloEngine PUBLIC TracyClient)
endif()
