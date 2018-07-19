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