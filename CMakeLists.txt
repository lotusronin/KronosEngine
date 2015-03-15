cmake_minimum_required (VERSION 2.8.11)

project (Platformer)
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory (src)
