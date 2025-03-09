#ifndef ENEMY_H
#define ENEMY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
struct Enemy
{   SDL_Texture* bird[2];
    std::vector <SDL_Texture*> objectTextures;
    int currentFrame;
    int frameDelay;
    float speed ;
    Uint32 lastFrameTime;
    SDL_Rect objectRects[6];
    SDL_Rect birdRect;
    int currentObjectIndex;
    bool isBirdActive;
    SDL_Rect predefinedCactusSizes[6];
    Enemy();
    void loadObjectTexture(SDL_Renderer* renderer);
    void updateBirdAnimation();
    void updateObjectPosition(SDL_Renderer* renderer);
    void freeObject_Texture();
    
};

#endif