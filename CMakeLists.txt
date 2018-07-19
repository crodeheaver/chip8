cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip8 main.cpp src/chip8.cpp include/chip8.h src/app.cpp include/app.h)

target_link_libraries(chip8 ${SDL2_LIBRARIES} )




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

add_custom_command(
        TARGET chip8 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/pong2.c8
        ${CMAKE_CURRENT_BINARY_DIR}/pong2.c8)