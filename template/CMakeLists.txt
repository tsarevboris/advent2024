cmake_minimum_required(VERSION 3.15)

SET(NAME "day__")
project(${NAME})

set(CMAKE_CXX_STANDARD 20)
SET(COMMON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../common)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

file(GLOB common_src "${COMMON_SOURCES}/src/*.cpp")

file(GLOB cpp_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB h_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(main main.cpp ${common_src})
target_include_directories(main PRIVATE ${COMMON_SOURCES}/include)
