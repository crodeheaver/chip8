//
// Created by colby on 7/18/18.
//
#include <iostream>
#include "../include/app.h"


App::App() {
    running = true;
    cpu.load("pong2.c8");
}

int App::OnExecute() {
    if(!OnInit()) {
        return -1;
    }

    SDL_Event Event;

    while(running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();

        if(cpu.soundFlag){
            beeper.beep(440, 100);
            beeper.wait();
            cpu.soundFlag = false;
        }
    }

    OnCleanup();

    return 0;
}

bool App::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    if ((window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN)) == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr){
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

void App::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        running = false;
    }

    if (Event->type == SDL_KEYDOWN){
        auto keyboardLocation = 0;
        switch (Event->key.keysym.sym)
        {
            case SDLK_1: keyboardLocation = 0x1; break;
            case SDLK_2: keyboardLocation = 0x2; break;
            case SDLK_3: keyboardLocation = 0x3; break;
            case SDLK_4: keyboardLocation = 0xC; break;
            case SDLK_q: keyboardLocation = 0x4; break;
            case SDLK_w: keyboardLocation = 0x5; break;
            case SDLK_e: keyboardLocation = 0x6; break;
            case SDLK_r: keyboardLocation = 0xD; break;

            case SDLK_a: keyboardLocation = 0x7; break;
            case SDLK_s: keyboardLocation = 0x8; break;
            case SDLK_d: keyboardLocation = 0x9; break;
            case SDLK_f: keyboardLocation = 0xE; break;
            case SDLK_z: keyboardLocation = 0xA; break;
            case SDLK_x: keyboardLocation = 0x0; break;
            case SDLK_c: keyboardLocation = 0xB; break;
            case SDLK_v: keyboardLocation = 0xF; break;
        }
        cpu.keyboard[keyboardLocation] = 1;
    }

    if (Event->type == SDL_KEYUP){
        auto keyboardLocation = 0;
        switch (Event->key.keysym.sym)
        {
            case SDLK_1: keyboardLocation = 0x1; break;
            case SDLK_2: keyboardLocation = 0x2; break;
            case SDLK_3: keyboardLocation = 0x3; break;
            case SDLK_4: keyboardLocation = 0xC; break;
            case SDLK_q: keyboardLocation = 0x4; break;
            case SDLK_w: keyboardLocation = 0x5; break;
            case SDLK_e: keyboardLocation = 0x6; break;
            case SDLK_r: keyboardLocation = 0xD; break;

            case SDLK_a: keyboardLocation = 0x7; break;
            case SDLK_s: keyboardLocation = 0x8; break;
            case SDLK_d: keyboardLocation = 0x9; break;
            case SDLK_f: keyboardLocation = 0xE; break;
            case SDLK_z: keyboardLocation = 0xA; break;
            case SDLK_x: keyboardLocation = 0x0; break;
            case SDLK_c: keyboardLocation = 0xB; break;
            case SDLK_v: keyboardLocation = 0xF; break;
        }
        cpu.keyboard[keyboardLocation] = 0;
    }
}

void App::OnLoop() {
    cpu.tick();
}

void App::OnRender() {
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    for(int y = 0; y < 32; ++y)
        for(int x = 0; x < 64; ++x) {
            if(cpu.display[(y * 64) + x] == 1) {
                SDL_Rect r = RectangleFactory(x*10, y*10);
                SDL_RenderFillRect( renderer, &r );
            }

    }
    SDL_RenderPresent(renderer);
}

void App::OnCleanup() {
    SDL_Quit();
}

SDL_Rect App::RectangleFactory(int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = 10;
    rect.w = 10;
    return rect;
}