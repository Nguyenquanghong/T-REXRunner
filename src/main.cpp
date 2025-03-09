
#include <data.h>
#include <graphic.h>
#include <loop.h>
#include <trex.h>
#include <core.h>
#include <background.h>
#include <enemy.h>


int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!InitSDL(window, renderer)) return -1;
    Trex trex;
    Background background;
    Enemy enemy;
    background.loadBackground_Texture(renderer);
    trex.loadTrex_Texture( renderer);
    enemy.loadObjectTexture(renderer);
    SDL_Event event;
    while(running){
        GameManager::updateSpeed();
        ProcessInput(running,trex);
    
        SDL_RenderClear(renderer);
        background.renderBackground_Texture(renderer);
        background.updateBackgroundPosition(renderer);
        trex.updatePhysic();
        trex.updateAnimation();
        trex.renderTrex_Texture(renderer);
        enemy.updateBirdAnimation();
        enemy.updateObjectPosition(renderer);


        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Giữ ~60 FPS
    }
    trex.freeTrex_Texture();
    background.freeBackground_Texture();
    CloseSDL(window,renderer);
    return 0;
}
