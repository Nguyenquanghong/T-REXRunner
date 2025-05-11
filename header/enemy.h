#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#include <trex.h>

struct Bullet {
    SDL_Rect rect;
    bool active;
    int speed;
};

struct Enemy {
    std::vector<SDL_Texture*> objectTextures;

    SDL_Rect objectRects[11];              // tăng lên 11 để chứa shooter
    SDL_Rect predefinedObjectSizes[11];

    int currentObjectIndex;

    // Bird animation
    bool birdMovingUp = true; 
    int birdFrame;
    int birdTotalFrames = 2;
    int birdFrameDelay = 80;
    Uint32 birdLastFrameTime;

    // Shiba animation
    int shibaFrame;
    int shibaTotalFrames = 6;
    int shibaFrameDelay = 30;
    Uint32 shibaLastFrameTime;

    // Doge animation
    int dogeFrame;
    int dogeTotalFrames = 6;
    int dogeFrameDelay = 50;
    Uint32 dogeLastFrameTime;

    // Anh animation
    int anhFrame;
    int anhTotalFrames = 6;
    int anhFrameDelay = 80;
    Uint32 anhLastFrameTime;
    //shooter animation
    int shooterFrame;
    int shooterTotalFrames = 6;
    int shooterFrameDelay = 300;
    Uint32 shooterLastFrameTime;

    // Bullet
    Bullet bullet;
    Uint32 lastBulletTime;
    Uint32 bulletCooldown = 1500;

    Enemy();
    void loadObjectTexture(SDL_Renderer* renderer);
    void updateObjectPosition(SDL_Renderer* renderer);
    bool checkCollision(const SDL_Rect& dinoRect);
    bool isEnemyOnScreen();
    void resetPosition();
    void freeEnemy_Texture();
};

#endif
