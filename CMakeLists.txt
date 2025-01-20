cmake_minimum_required(VERSION 3.30)
project(tetris C)

set(CMAKE_C_STANDARD 11)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(tetris main.c
        matrix.c
        matrix.h
        tetris_shape.c
        tetris_shape.h)

target_link_libraries(tetris ${SDL2_LIBRARIES})