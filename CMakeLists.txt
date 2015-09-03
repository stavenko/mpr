cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR MultipassRenderer)
project(MPR C CXX)

include(ExternalProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(MPR_SOURCES ${MPR_SOURCE_DIR}/src)
set(MPR_INCLUDES ${MPR_SOURCE_DIR}/include)

set(GLFW_BUILD_TESTS OFF CACHE BOOL "Do not build Tests")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Do not build examples")

find_package(Boost REQUIRED)

add_subdirectory(${MPR_SOURCE_DIR}/external/glfw)
add_subdirectory(${MPR_SOURCE_DIR}/external/gtest)
include_directories(${MPR_SOURCE_DIR}/external/glfw/include)

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

