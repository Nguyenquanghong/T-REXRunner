#ifndef TREX_H
#define TREX_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
struct Trex{
    SDL_Texture* trex_run[2];
    SDL_Texture* trex_jump;
    SDL_Texture* trex_bow[2];
    int currentFrame;
    int frameDelay;
    Uint32 lastFrameTime;
    SDL_Rect trexRect;
    float velocityY;
    bool isDucking;
    bool isJumping;
    bool fastFall;
    
    Trex();
    bool onGround();
    void trexNormal();
    void trexDucking();
    void trexJumping();
    void updatePhysic();
    void updateAnimation();
    void loadTrex_Texture(SDL_Renderer* renderer);
    void renderTrex_Texture(SDL_Renderer* renderer);
    void freeTrex_Texture();
};

#endif