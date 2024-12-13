cmake_minimum_required(VERSION 3.22)
project(src LANGUAGES CXX)

# Option to enable TODO messages
option(ENABLE_TODO "Enable compile-time TODO messages" ON)

if (ENABLE_TODO)
    add_compile_definitions(ENABLE_TODO)
endif ()

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE CPP_SOURCE "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HPP_SOURCE "${SOURCE_DIR}/*.hpp")

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
add_executable(${PROJECT_NAME} ${CPP_SOURCE} ${HPP_SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME} PRIVATE "${SOURCE_DIR}/pch.hpp")
target_link_libraries(${PROJECT_NAME} PRIVATE external)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:HV_DEBUG_BUILD>"
        "$<$<CONFIG:Release>:HV_RELEASE_BUILD>"
)