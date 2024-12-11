set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

file(GLOB DAY_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(DAY day10)

add_executable(${DAY} main.cpp ${COMMON_SRC} ${DAY_SRC})

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}")
set(RESOURCE_FILES input.txt)
foreach(resource_file ${RESOURCE_FILES})
    configure_file(${resource_file} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ COPYONLY)
endforeach()

target_include_directories(${DAY} PRIVATE ${COMMON_INCLUDE})
target_compile_options(${DAY} PRIVATE -Wall -Werror -Wextra)
