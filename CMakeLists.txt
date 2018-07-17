cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

add_executable(chip8 main.cpp src/chip8.cpp include/chip8.h)

add_custom_command(
        TARGET chip8 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Breakout.ch8
        ${CMAKE_CURRENT_BINARY_DIR}/Breakout.ch8)