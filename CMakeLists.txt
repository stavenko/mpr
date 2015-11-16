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
find_package(OpenGL REQUIRED)
find_package(Git REQUIRED)
find_package(GLEW REQUIRED)
FIND_PATH(
CIMG_INCLUDE_DIR CImg.h
/usr/lib/CImg
/usr/local/lib/CImg
/opt/local/lib/CImg
"${CMAKE_CURRENT_SOURCE_DIR}/CImg"
)

message(INFO, ${CIMG_INCLUDE_DIR})
SET(CIMG_FOUND FALSE)
 IF(CIMG_INCLUDE_DIR)
 SET(CIMG_FOUND TRUE)
 INCLUDE_DIRECTORIES(${CIMG_INCLUDE_DIR})
ELSE(CIMG_INCLUDE_DIR)
 MESSAGE(FATAL ERROR "CImg.h not found - Please install CImg")
ENDIF(CIMG_INCLUDE_DIR)

add_subdirectory(${MPR_SOURCE_DIR}/external/glfw)
add_subdirectory(${MPR_SOURCE_DIR}/external/gtest)
add_subdirectory(${MPR_SOURCE_DIR}/external/glm)
include_directories(${MPR_SOURCE_DIR}/external/glfw/include)
include_directories(${GLM_INCLUDE_DIR})
#include_directories(${IL_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)

