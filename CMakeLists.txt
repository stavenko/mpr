cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR MultipassRenderer)
project(MPR C CXX)

include(ExternalProject)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(MPR_SOURCES ${MPR_SOURCE_DIR}/src)
set(MPR_INCLUDES ${MPR_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(examples)
