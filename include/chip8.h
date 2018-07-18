//
// Created by colby on 7/11/18.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H
#include <array>
#include <stack>
#include <string>
#include <cstdint>

class chip8 {
  private:
    std::uint16_t pcounter;
    std::uint16_t I;

    std::uint8_t displaytimer;
    std::uint8_t soundtimer;

    std::array<std::uint8_t, 4096> memory;
    std::array<std::uint8_t, 16> V;
    std::array<std::uint8_t, 16> keyboard;
    std::array<bool, 2048> display;

    std::stack<std::uint16_t> stack;

    bool drawFlag;

    union {
      std::uint16_t opcode;
      struct {
        unsigned int N : 4;
        unsigned int Y : 4;
        unsigned int X : 4;
        unsigned int A : 4;
      };
      struct {
        unsigned short low : 8;
        unsigned short high : 8;
      };
    };

    void initialize();
  public:
    chip8();
    ~chip8();

    void tick();

    void load(const std::string& fileName);
};


#endif //CHIP8_CHIP8_H
