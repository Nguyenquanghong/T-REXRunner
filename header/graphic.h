#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

struct GameManager {
    static float speedMultiplier; // Nhân tốc độ chung
    static Uint32 lastUpdateTime;
    static void updateSpeed();
};

struct Score {
    TTF_Font* font;
    int value;
    Uint32 lastUpdate;
    std::vector<int> highScores;

    Score();
    void update();
    void render(SDL_Renderer* renderer);
    void renderHighScore(SDL_Renderer* renderer);
    void loadHighScore();
    void saveHighScore();
    void freeFont();
};

void loadSound();

struct SpeedController {
    static float baseSpeed;
    static float speedMultiplier;
    static Uint32 lastUpdateTime;

    static void updateSpeed(bool oEnemiesOnScreen);
    static float getSpeed();
    static void resetSpeed();
};

#endif
