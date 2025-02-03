cmake_minimum_required(VERSION 3.13.0)
project(PurpleHole VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_subdirectory(vendor)
add_subdirectory(include)
add_subdirectory(src)
