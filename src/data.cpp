#include <data.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

    bool running = true;
    const float WINDOW_WIDTH = 700;
    const int WINDOW_HEIGHT = 500;
    // background
    const Uint32 TIME_INCREASE_SPEED = 8000;
    float BG_SPEED = 4.0f;
    float BG_X = 0.0f;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastSpeedIncreaseTime = SDL_GetTicks();
    const int BG_Y =(2*WINDOW_HEIGHT)/3;
    const int BG_HEIGHT =WINDOW_HEIGHT - BG_Y;
    const int BG_WIDTH = WINDOW_WIDTH;
    
    //trex
    const double JUMP_FORCE = -12;
    const double GRAVITY = 0.5;
    const int TREX_X = 20;
    const int TREX_Y = BG_Y+32;
    const int TREX_WIDTH = 50;
    const int TREX_HEIGHT = 50;
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    Trex trex;
    Background background;
    Enemy enemy;
    Score score;
    // sound
    Mix_Chunk* jumpSound = nullptr;
    Mix_Chunk* dieSound = nullptr;
    Mix_Chunk* scoreSound = nullptr;
    Mix_Music* backgroundSound  = nullptr;
    
