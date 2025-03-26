#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
struct Background{
    SDL_Texture* bgColor;
    std::vector <SDL_Texture*> bgTextures;
    SDL_Texture* overGameBg;
    SDL_Texture* restartButton;
    void loadBackground_Texture(SDL_Renderer* renderer);
    void renderBackground_Texture(SDL_Renderer* renderer);
    void updateBackgroundPosition(SDL_Renderer* renderer);
    void resetPosition();
    void renderOverGameBackground_Texture(SDL_Renderer* renderer);
    void renderRestartButton(SDL_Renderer* renderer);
    void freeBackground_Texture();
};

#endif
