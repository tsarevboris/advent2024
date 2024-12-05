cmake_minimum_required(VERSION 3.15)

project(advent2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/common")
set(COMMON_INCLUDE "${COMMON_DIR}/include")
file(GLOB COMMON_SRC "${COMMON_DIR}/src/*.cpp")

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
