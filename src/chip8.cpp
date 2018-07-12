//
// Created by colby on 7/11/18.
//

#include "../include/chip8.h"

chip8::chip8(const char *filename) {

}

void chip8::initialize() {
  pcounter = 0x200;
  opcode = 0;
  I = 0;
  stackpointer = 0;

  memory.fill(0);
  V.fill(0);
  stack.fill(0);
  display.fill(0);
  input.fill(0);
}