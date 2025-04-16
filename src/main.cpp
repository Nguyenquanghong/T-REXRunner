
#include <data.h>
#include <graphic.h>
#include <loop.h>
#include <trex.h>
#include <core.h>
#include <background.h>
#include <enemy.h>


int main(int argc, char* argv[]) {
    //khoi tao
    if (!InitSDL(window, renderer)) return -1;
    if (!InitMixer()) return -1;
    if (TTF_Init() == -1) {
        SDL_Log(" TTF_Init failed: %s", TTF_GetError());
        return -1;
    }

    // load anh + sound
    background.loadBackground_Texture(renderer);
    trex.loadTrex_Texture( renderer);
    enemy.loadObjectTexture(renderer);

    loadSound();

    //run game 
    rungame();

    // giai phong
    enemy.freeEnemy_Texture();
    trex.freeTrex_Texture();
    background.freeBackground_Texture();
    CloseSDL(window,renderer);
    CloseMixer();
    return 0;
}
