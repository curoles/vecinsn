cmake_minimum_required(VERSION 3.16)

#@author: Igor Lesik 2020-2021
project(VX)

# Requires C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Install inside the build directory.
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

include_directories(.)

enable_testing()

include(compile.cmake)

add_subdirectory(vx)
add_subdirectory(test)
