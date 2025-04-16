#include <loop.h>
#include <trex.h>
#include <enemy.h>
#include <background.h>
#include <data.h>
#include <iostream>

void rungame() {
    bool isOver = false;
    bool soundPlayed = false; // Biến kiểm soát âm thanh chết
    bool firstPlay = true;

    while (running) {
        if (enemy.checkCollision(trex.trexRect)) {
            if (!isOver) {
                isOver = true;
                Mix_PlayChannel(-1, dieSound, 0);
                soundPlayed = true;
                SDL_Delay(700);
            }
        }
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && isOver) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                SDL_Rect restartButton = { (int)WINDOW_WIDTH / 2 - 25, (int)WINDOW_HEIGHT / 2 - 10, 50, 50 };
                if (mouseX >= restartButton.x && mouseX <= (restartButton.x + restartButton.w) &&
                    mouseY >= restartButton.y && mouseY <= (restartButton.y + restartButton.h)) {
                    Mix_HaltMusic();
                    isOver = false;
                    soundPlayed = false;
                    trex.resetPosition();
                    background.resetPosition();
                    enemy.resetPosition();
                    score.value = 0;
                }
            }
            else if (!isOver) {
                if (firstPlay) {
                    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                        firstPlay = false; // Đã bắt đầu → lần sau không cần nữa
                    }
                }
                else{
                    if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_DOWN) trex.trexDucking();
                        if (event.key.keysym.sym == SDLK_UP) trex.trexJumping();
                    }
                    else if (event.type == SDL_KEYUP) {
                        if (event.key.keysym.sym == SDLK_DOWN) trex.trexNormal();
                        if (event.key.keysym.sym == SDLK_UP) trex.trexJumping();
                    }
                }
            }
        }

        // Vẽ màn hình
        SDL_RenderClear(renderer);

        if (isOver) {
            Mix_VolumeMusic(15);
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(backgroundSound, -1);
            }
            background.renderOverGameBackground_Texture(renderer);
            background.renderRestartButton(renderer);
        } else {
            if (firstPlay) {
                background.renderStartGameBackground_Texture(renderer);
            } else {
                background.renderBackground_Texture(renderer);
                background.updateBackgroundPosition(renderer);

                trex.updatePhysic();
                trex.updateAnimation();
                trex.renderTrex_Texture(renderer);

                enemy.updateBirdAnimation();
                enemy.updateObjectPosition(renderer);
                score.update();
                score.render(renderer);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}