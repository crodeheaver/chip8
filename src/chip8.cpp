//
// Created by colby on 7/11/18.
//

#include "../include/chip8.h"
#include <iostream>
#include <fstream>

using namespace std;

chip8::chip8() = default;
chip8::~chip8() = default;

void chip8::initialize() {
  pcounter = 0x200;
  opcode = 0;
  I = 0;

  memory.fill(0);
  V.fill(0);
  display.fill(false);
  input.fill(0);
}

void chip8::load(const std::string &fileName) {
  initialize();

  ifstream program(fileName, std::ios::binary);

  program.seekg( 0, ios::end );

  streamoff len = program.tellg();

  program.seekg(0, ios::beg);

  auto startLocation = (char*)memory.data() + 0x200;

  program.read(startLocation, len);

  program.close();
}

void chip8::tick() {
  opcode = memory[pcounter] << 8u | memory[pcounter + 1u];

  switch(opcode & 0xF000u){
    case 0x0000:
      break;
    case 0x1000:
      pcounter = opcode & (uint8_t)0x0FFF;
      break;
    case 0x2000:
      stack.push(pcounter);
      pcounter = opcode & (uint8_t)0x0FFF;
      break;
    case 0x3000:
      if(V[opcode & 0x0F00u] == opcode & 0x00FFu) {
        pcounter += 4;
      }
      break;
    case 0x4000:
      if(V[opcode & 0x0F00u] != opcode & 0x00FFu) {
        pcounter += 4;
      }
      break;
    case 0x5000:
      if(V[opcode & 0x0F00u] == V[opcode & 0x00F0u]) {
        pcounter += 4;
      }
      break;
    case 0x6000:
      V[opcode & 0x0F00u] = (uint8_t)(opcode & 0x00FFu);
      pcounter += 2;
      break;

    case 0x7000:
      V[opcode & 0x0F00u] = (uint8_t)(V[opcode & 0x0F00u] + (opcode & 0x00FFu));
      pcounter += 2;
      break;
    default:
      break;
  }
}