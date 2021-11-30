cmake_minimum_required(VERSION 3.12)

project(ascii-chart)

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(ascii-chart ${SRC_FILES})
 
add_custom_command(
    TARGET ascii-chart 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ascii-chart> ..
                   )