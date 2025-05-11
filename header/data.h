#ifndef DATA_H
#define DATA_H
#include <bits/stdc++.h> 
#include <SDL2/SDL.h>
#include <trex.h>
#include <background.h>
#include <enemy.h>
#include <graphic.h>

    extern bool running;
    extern const float WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;
   
    //background
    extern const Uint32 TIME_INCREASE_SPEED;
    extern float BG_SPEED;
    extern float BG_X;
    extern Uint32 lastTime;
    extern Uint32 lastSpeedIncreaseTime;
    extern const int BG_Y;
    extern const int BG_HEIGHT;
    extern const int BG_WIDTH;
    extern const int cloud_speed;
    extern int cloud_x;
    // trex
    extern const double JUMP_FORCE;
    extern const double GRAVITY;
    extern const int TREX_X;
    extern const int TREX_Y;
    extern const int TREX_WIDTH;
    extern const int TREX_HEIGHT;
    //bird
    extern float BIRD_X;
    extern const int BIRD_WIDTH;
    extern const int BIRD_HEIGHT;
    // khai bao
    extern Trex trex;
    extern Background background;
    extern Enemy enemy;
    extern Score score;
    extern SDL_Window* window;
    extern SDL_Renderer* renderer;
    //sound 
    extern Mix_Chunk* jumpSound;
    extern Mix_Chunk* dieSound;
    extern Mix_Chunk* scoreSound;
    extern Mix_Chunk* click;
    extern Mix_Music* backgroundSound;


#endif