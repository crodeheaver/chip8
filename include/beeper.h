//
// Created by colby on 7/20/18.
//

#ifndef CHIP8_BEEPER_H
#define CHIP8_BEEPER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <queue>
#include <cmath>

struct BeepObject
{
    double freq;
    int samplesLeft;
};

class Beeper
{
private:
    double v;
    std::queue<BeepObject> beeps;

public:
    Beeper();
    ~Beeper();
    void beep(double freq, int duration);
    void generateSamples(Sint16 *stream, int length);
    void wait();
};


#endif //CHIP8_BEEPER_H
