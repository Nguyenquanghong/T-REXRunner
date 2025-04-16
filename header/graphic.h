#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

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
        Score();
        void update();
        void render(SDL_Renderer* renderer);
        void freeFont();
    };

    void loadSound();
#endif