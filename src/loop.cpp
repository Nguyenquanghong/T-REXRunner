#include <loop.h>
#include <trex.h>
    void ProcessInput(bool &running,Trex &character){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if(event.type== SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_DOWN) character.trexDucking();
                if(event.key.keysym.sym == SDLK_UP) character.trexJumping();
            }
            else if(event.type == SDL_KEYUP) {
                if(event.key.keysym.sym == SDLK_DOWN) character.trexNormal();
                if(event.key.keysym.sym == SDLK_UP)  character.trexJumping();
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_DOWN) {
                    character.trexNormal();
                }
            }
        }
    }