cmake_minimum_required(VERSION 3.30)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(SDL/SDL_ttf-release-2.24.0)
add_subdirectory(SDL/SDL-release-2.30.10)

find_package(SDL2 REQUIRED)

add_executable(tetris main.c
        matrix.c
        matrix.h
        tetris_shape.c
        tetris_shape.h)

target_link_libraries(tetris PRIVATE SDL2 SDL2_ttf)

#TODO: Test on windows
if (WIN32)
    target_link_libraries(
            Sandbox PRIVATE SDL2main
    )
endif()

add_custom_command(
        TARGET tetris POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SDL2>"
        "$<TARGET_FILE:SDL2_ttf>"
        "$<TARGET_FILE_DIR:tetris>"
        VERBATIM
)
