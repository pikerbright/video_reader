cmake_minimum_required(VERSION 3.2)
set(PROJECT_NAME stream)

project(${PROJECT_NAME})

option(USE_OpenCV "Use OpenCV to read, write and show image" ON)

set(OpenCV_DIR "/usr/local/opencv-3.3.0" CACHE PATH "OpenCV root directory")

if (NOT CMAKE_INSTALL_PREFIX)
  message(STATUS "CMake install prefix not set - defaulting to ${CMAKE_BINARY_DIR}/distribute")
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/distribute)
endif ()

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type not set - defaulting to Release")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build from: Release Debug." FORCE)
endif ()

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif ()

include(cmake/Utils.cmake)
include(cmake/Dependencies.cmake)
message(STATUS ${PROJECT_NAME})
add_subdirectory(src)

