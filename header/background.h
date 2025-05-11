#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
struct Background{
    SDL_Texture* bgColor;
    std::vector <SDL_Texture*> bgTextures;
    SDL_Texture* startGameBg;
    SDL_Texture* overGameBg;
    SDL_Texture* pauseGameBg;
    SDL_Texture* cloud;
    SDL_Texture* sun;
    SDL_Texture* pause_icon;
    SDL_Texture*pause_icon2;
    SDL_Texture* highScoreGameBg;
    
    void loadBackground_Texture(SDL_Renderer* renderer);
    void renderBackground_Texture(SDL_Renderer* renderer);
    void renderSunCloud_Texture(SDL_Renderer* renderer);
    void renderPause_Texture(SDL_Renderer* renderer);
    void updateBackgroundPosition(SDL_Renderer* renderer);
    void resetPosition();
    void renderStartGameBackground_Texture(SDL_Renderer* renderer);
    void renderOverGameBackground_Texture(SDL_Renderer* renderer);
    void renderPauseGameBackground_Texture(SDL_Renderer* renderer);
    void renderHighScore_Texture(SDL_Renderer* renderer);
    void freeBackground_Texture();
};

#endif
