//
// Created by colby on 7/11/18.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H
#include <array>
#include <stack>
#include <string>

class chip8 {
  private:
    uint16_t pcounter;
    uint16_t I;
    uint16_t opcode;

    uint8_t displaytimer;
    uint8_t soundtimer;

    std::array<uint8_t, 4096> memory;
    std::array<uint8_t, 16> V;
    std::array<uint8_t, 16> input;
    std::array<bool, 2048> display;

    std::stack<uint16_t> stack;

    void initialize();
  public:
    chip8();
    ~chip8();

    void tick();

    void load(const std::string& fileName);
};


#endif //CHIP8_CHIP8_H
