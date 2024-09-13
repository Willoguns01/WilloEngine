cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)

project(WilloEngineProject)

add_subdirectory(external)

# temporary
set(WILLO_ENGINE_BUILD_EDITOR true)
set(WILLO_ENGINE_BUILD_RUNTIME true)

if (WILLO_ENGINE_BUILD_EDITOR)
    set(WILLO_ENGINE_BUILD_ENGINE true)
endif()
if (WILLO_ENGINE_BUILD_RUNTIME)
    set(WILLO_ENGINE_BUILD_ENGINE true)
endif()

if (WILLO_ENGINE_BUILD_ENGINE)
    add_subdirectory(WilloEngine)
endif()

if (WILLO_ENGINE_BUILD_EDITOR)
    add_subdirectory(WilloEditor)
endif()

if (WILLO_ENGINE_BUILD_RUNTIME)
    add_subdirectory(WilloRuntime)
endif()
