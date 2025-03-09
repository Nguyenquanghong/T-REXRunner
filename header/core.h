#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

    bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer);
    void CloseSDL(SDL_Window* window, SDL_Renderer* renderer);
#endif