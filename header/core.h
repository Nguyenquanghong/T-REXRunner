#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

    bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer);
    bool InitMixer();
    void CloseSDL(SDL_Window* window, SDL_Renderer* renderer);
    void CloseMixer();
#endif