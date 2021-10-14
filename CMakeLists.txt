cmake_minimum_required(VERSION 3.0)

project(ascii-chart)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(ascii-chart main.c chart/chart.c fileHandler/fileHandler.c)
 