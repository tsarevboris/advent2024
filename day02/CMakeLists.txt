set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

file(GLOB DAY_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(day02 main.cpp ${COMMON_SRC} ${DAY_SRC})

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}")
set(RESOURCE_FILES input.txt)
foreach(resource_file ${RESOURCE_FILES})
    configure_file(${resource_file} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ COPYONLY)
endforeach()

target_include_directories(day02 PRIVATE ${COMMON_INCLUDE})
