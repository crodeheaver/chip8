cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

add_executable(chip8 main.cpp src/chip8.cpp include/chip8.h)