#include <iostream>
#include "include/chip8.h"

int main() {
    chip8 chip;
    chip.load("Breakout.ch8");
    chip.tick();
    return 0;
}