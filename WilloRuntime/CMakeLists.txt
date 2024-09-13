# WilloRuntime

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(WilloRuntime)
add_executable(WilloRuntime src/main.cpp)
target_link_Libraries(WilloRuntime PRIVATE WilloEngine)
