cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(chip8 main.cpp src/chip8.cpp include/chip8.h)

target_link_libraries(chip8 ${CURSES_LIBRARIES})

add_custom_command(
        TARGET chip8 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Breakout.ch8
        ${CMAKE_CURRENT_BINARY_DIR}/Breakout.ch8)

add_custom_command(
        TARGET chip8 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/IBM.ch8
        ${CMAKE_CURRENT_BINARY_DIR}/IBM.ch8)