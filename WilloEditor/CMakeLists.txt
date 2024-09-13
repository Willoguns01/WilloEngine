# WilloEditor

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

option(WILLO_EDITOR_ENABLE_PROFILING "Enable profiling for WilloEditor" ON)

project(WilloEditor)
add_executable(WilloEditor src/main.cpp)
target_link_libraries(WilloEditor PRIVATE WilloEngine)

if (WILLO_EDITOR_ENABLE_PROFILING)
    target_link_libraries(WilloEditor PUBLIC TracyClient)
endif()
