//
// Created by colby on 7/18/18.
//

#ifndef CHIP8_APP_H
#define CHIP8_APP_H
#include <SDL2/SDL.h>
#include <array>
#include "chip8.h"
#include "beeper.h"


class App {
private:
    chip8 cpu;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Rect RectangleFactory(int x, int y);
    Beeper beeper;

public:
    bool running;
    App();

    int OnExecute();

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();

};


#endif //CHIP8_APP_H
