# WilloEditor

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(WilloEditor)
add_executable(WilloEditor src/main.cpp)
target_link_libraries(WilloEditor PRIVATE WilloEngine)

if (WILLO_ENGINE_ENABLE_PROFILING)
    target_link_libraries(WilloEditor PRIVATE TracyClient)
    target_compile_definitions(WilloEditor PRIVATE WILLO_ENGINE_ENABLE_PROFILING)
endif()
