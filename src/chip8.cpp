//
// Created by colby on 7/11/18.
//

#include "../include/chip8.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

uint8_t fontset[80] =
        {
                0xF0, 0x90, 0x90, 0x90, 0xF0, //0
                0x20, 0x60, 0x20, 0x20, 0x70, //1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
                0x90, 0x90, 0xF0, 0x10, 0x10, //4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
                0xF0, 0x10, 0x20, 0x40, 0x40, //7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
                0xF0, 0x90, 0xF0, 0x90, 0x90, //A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
                0xF0, 0x80, 0x80, 0x80, 0xF0, //C
                0xE0, 0x90, 0x90, 0x90, 0xE0, //D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
                0xF0, 0x80, 0xF0, 0x80, 0x80  //F
        };

chip8::chip8() = default;
chip8::~chip8() = default;

void chip8::initialize() {
  pcounter = 0x200;
  opcode = 0;
  I = 0;

  memory.fill(0);
  V.fill(0);
  display.fill(false);
  keyboard.fill(0);

    for(int i = 0; i < 80; ++i)
        memory[i] = fontset[i];
}

bool chip8::load(const std::string &fileName) {
  initialize();

  ifstream program(fileName, std::ios::binary);

  program.seekg( 0, ios::end );

  streamoff len = program.tellg();

  program.seekg(0, ios::beg);

  auto startLocation = (char*)memory.data() + 0x200;

  program.read(startLocation, len);

  program.close();
  return true;
}

void chip8::tick() {
  opcode = memory[pcounter] << 8u | memory[pcounter + 1u];

  switch(A){
    case 0x0:
      switch(low){
        case 0xE0:
          display.fill(0);
          drawFlag = true;
          pcounter+=2;
          break;
        case 0xEE:
          pcounter = stack.top();
          stack.pop();
          pcounter += 2;
          break;
        default:
          cout << "Unrecognized command " << std::hex << opcode << "\n";
      }
      break;
    case 0x1:
      pcounter = opcode & 0x0FFFu;
      break;
    case 0x2:
      stack.push(pcounter);
      pcounter = opcode & 0x0FFFu;
      break;
    case 0x3:
      if(V[X] == low) {
        pcounter += 2;
      }
      pcounter += 2;
      break;
    case 0x4:
      if(V[X] != low) {
        pcounter += 2;
      }
      pcounter += 2;
      break;
    case 0x5:
      if(V[X] == V[Y]) {
        pcounter += 2;
      }
      pcounter += 2;
      break;
    case 0x6:
      V[X] = low;
      pcounter += 2;
      break;

    case 0x7:
      V[X] = V[X] + low;
      pcounter += 2;
      break;
    case 0x8:
      switch(N){
        case 0x0:
          V[X] = V[Y];
          pcounter+=2;
          break;
        case 0x1:
          V[X] = V[X] | V[Y];
          pcounter+=2;
          break;
        case 0x2:
          V[X] = V[X] & V[Y];
          pcounter+=2;
          break;
        case 0x3:
          V[X] = V[X] ^ V[Y];
          pcounter+=2;
          break;
        case 0x4: {
          unsigned int value = V[X] + V[Y];
          V[X] = (uint8_t) value;
          if (value > 255)
            V[0xF] = 1;
          else
            V[0xF] = 0;
          pcounter += 2;
          break;
        }
        case 0x5: {
          if (V[X] > V[Y])
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[X] = V[X] - V[Y];
          pcounter += 2;
          break;
        }
        case 0x6:
          if((V[X] & 0x0001) == 1)
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[X] = V[X] / 2;
          pcounter+=2;
          break;
        case 0x7:
          if(V[Y] > V[X])
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[X] = V[Y] - V[X];
          pcounter+=2;
          break;
        case 0xE:
          if((V[X] & 0xA000) == 1)
            V[0xF] = 1;
          else
            V[0xF] = 0;
          V[X] = V[X] * 2;
          pcounter+=2;
          break;
        default:
          cout << "Unrecognized command " << std::hex << opcode << "\n";
      }
      break;
    case 0x9:
      if(V[X] != V[Y])
        pcounter += 2;
      pcounter += 2;
      break;
    case 0xA:
      I = NNN;
      pcounter += 2;
      break;
    case 0xB:
      pcounter = NNN + V[0];
      break;
    case 0xC: {
      std::default_random_engine generator;
      std::uniform_int_distribution<short> distribution(0,255);
      auto random = distribution(generator);
      V[X] = random & low;
      pcounter +=2;
      break;
    }
    case 0xD: {
      unsigned short x = V[X];
      unsigned short y = V[Y];
      unsigned short height = N;
      unsigned short pixel;

      V[16] = 0;
      for (int yline = 0; yline < height; yline++)
      {
        pixel = memory[I + yline];
        for(int xline = 0; xline < 8; xline++)
        {
          if((pixel & (0x80 >> xline)) != 0)
          {
            if(display[(x + xline + ((y + yline) * 64))] == 1)
            {
              V[0xF] = true;
            }
            display[x + xline + ((y + yline) * 64)] ^= 1;
          }
        }
      }

      drawFlag = true;
      pcounter += 2;
      break;
    }
    case 0xE:
      switch(low){
        case 0x9E:
          if(keyboard[V[X]] != 0)
            pcounter+=2;
          pcounter+=2;
          break;
        case 0xA1:
          if(keyboard[V[X]] == 0)
            pcounter+=2;
          pcounter+=2;
          break;
        default:
          cout << "Unrecognized command " << std::hex << opcode << "\n";
      }
      break;
    case 0xF:
      switch(low){
        case 0x07:
          V[X] = displaytimer;
          pcounter += 2;
          break;
        case 0x0A: {
          bool keyPress = false;

          for(int i = 0; i < 16; ++i)
          {
            if(keyboard[i] != 0)
            {
              V[X] = i;
              keyPress = true;
            }
          }

          // If we didn't received a keypress, skip this cycle and try again.
          if(!keyPress)
            return;
          pcounter += 2;
          break;
        }
        case 0x15:
          displaytimer = V[X];
          pcounter += 2;
          break;
        case 0x18:
          soundtimer = V[X];
          pcounter += 2;
          break;
        case 0x1E:
          I = I + V[X];
          pcounter += 2;
          break;
        case 0x29:
          I = V[X] * 0x5u;
          pcounter += 2;
          break;
        case 0x33:
          memory[I] = V[X] / 100;
          memory[I] = (V[X] / 10) % 10;
          memory[I] = (V[X] % 100) % 10;
          pcounter += 2;
          break;
        case 0x55:
          for(auto i = 0; i < X; i++){
            memory[i + I] = V[i];
          }
          pcounter += 2;
          break;
        case 0x65:
          for(auto i = 0; i < X; i++){
            V[i] = memory[i + I];
          }
          pcounter += 2;
          break;
        default:
          cout << "Unrecognized command " << std::hex << opcode << "\n";
          break;
      }
      break;
    default:
      cout << "Unrecognized command " << std::hex << opcode << "\n";
      break;
  }

  if(displaytimer > 0)
    displaytimer -= 1;

  if(soundtimer > 0)
    soundtimer -= 1;

  if(soundtimer == 1)
    cout << "beep" << "\n";

}