//
// Created by colby on 7/11/18.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H
#include <array>

class chip8 {
  private:
    unsigned short pcounter;
    unsigned short I;
    unsigned short opcode;
    unsigned short stackpointer;

    unsigned char displaytimer;
    unsigned char soundtimer;

    std::array<unsigned char, 4096> memory;
    std::array<unsigned char, 16> V;
    std::array<unsigned char, 16> input;
    std::array<unsigned short, 16> stack;
    std::array<bool, 2048> display;

  public:
    chip8(const char* filename);
    ~chip();

    void initialize();

    void tick();
};


#endif //CHIP8_CHIP8_H
