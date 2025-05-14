#include <loop.h>
#include <trex.h>
#include <enemy.h>
#include <background.h>
#include <data.h>
#include <iostream>

void rungame() {
    bool isOver = false;
    bool soundPlayed = false;
    bool playgame = false;
    bool exit = false;
    bool pause = false;
    bool showHighScore = false;

    while (running) {
        // kiểm tra va chạm
        if (enemy.checkCollision(trex.trexRect)) {
            if (!isOver) {
                isOver = true;
                playgame = false;
                pause = false;
                Mix_PlayChannel(-1, dieSound, 0);
                SDL_Delay(700);
                score.saveHighScore(); 
            }
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                // xu lí đóng highscore
                if (showHighScore) {
                    SDL_Rect closeHighScoreButton = {497,18,31,37};
                    if (mouseX >= closeHighScoreButton.x && mouseX <= closeHighScoreButton.x + closeHighScoreButton.w &&
                        mouseY >= closeHighScoreButton.y && mouseY <= closeHighScoreButton.y + closeHighScoreButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        showHighScore = false;
                    }
                }

                // giao diện Game Over
                if (isOver && !playgame && !pause) {
                    SDL_Rect restartButton = {210, 112, 135, 49};
                    SDL_Rect backButton = {210, 168, 135, 49};
                    SDL_Rect exitButton = {210, 224, 135, 49};

                    if (mouseX >= restartButton.x && mouseX <= restartButton.x + restartButton.w &&
                        mouseY >= restartButton.y && mouseY <= restartButton.y + restartButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        Mix_HaltMusic();
                        isOver = false;
                        playgame = true;
                        soundPlayed = false;
                        trex.resetPosition();
                        background.resetPosition();
                        enemy.resetPosition();
                        score.value = 0;
                        SpeedController::resetSpeed();
                    }

                    else if (mouseX >= backButton.x && mouseX <= backButton.x + backButton.w &&
                             mouseY >= backButton.y && mouseY <= backButton.y + backButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        Mix_HaltMusic();
                        isOver = false;
                        soundPlayed = false;
                        trex.resetPosition();
                        background.resetPosition();
                        enemy.resetPosition();
                        score.value = 0;
                        SpeedController::resetSpeed();
                    }

                    else if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.w &&
                             mouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        running = false;
                    }
                }

                // giao diện bắt đầu
                else if (!playgame && !isOver && !pause) {
                    SDL_Rect playButton = {205, 84, 147, 42};
                    SDL_Rect highScoreButton = {205, 137, 147, 42};
                    SDL_Rect exitButton = {205, 189, 147, 42};
                    SDL_Rect closeHighScoreButton = {530, 10, 40, 40};

                    if (mouseX >= playButton.x && mouseX <= playButton.x + playButton.w &&
                        mouseY >= playButton.y && mouseY <= playButton.y + playButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        playgame = true;
                    }

                    else if (mouseX >= exitButton.x && mouseX <= exitButton.x + exitButton.w &&nmouseY >= exitButton.y && mouseY <= exitButton.y + exitButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        running = false;
                    }
                    else if (mouseX >= highScoreButton.x && mouseX <= highScoreButton.x + highScoreButton.w && mouseY >= highScoreButton.y && mouseY <= highScoreButton.y + highScoreButton.h) {
                        Mix_PlayChannel(-1, click, 0);
                        showHighScore = true;
                    }
                }

            } else if (!isOver && playgame) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_DOWN) trex.trexDucking();
                    if (event.key.keysym.sym == SDLK_UP) trex.trexJumping();
                    if (event.key.keysym.sym == SDLK_SPACE){
                        Mix_PlayChannel(-1, click, 0);
                        pause =!pause;
                    } 
                } else if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_DOWN) trex.trexNormal();
                    if (event.key.keysym.sym == SDLK_UP) trex.trexJumping();
                }
            }
        }

    
        SpeedController::updateSpeed(!enemy.isEnemyOnScreen());


        SDL_RenderClear(renderer);

        if (showHighScore) {
            background.renderHighScore_Texture(renderer);
            score.loadHighScore();
            score.renderHighScore(renderer);
        }
        else if (!playgame && !isOver && !pause) {
            background.renderStartGameBackground_Texture(renderer);
        }
        else if (isOver && !playgame && !pause) {
            Mix_VolumeMusic(15);
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(backgroundSound, -1);
            }
            background.renderOverGameBackground_Texture(renderer);
            score.render(renderer);

        }
        else if (pause && playgame && !isOver) {
            background.renderPauseGameBackground_Texture(renderer);
            background.renderPause_Texture(renderer);
        }
        else if (playgame && !pause && !isOver) {
            background.renderBackground_Texture(renderer);
            background.updateBackgroundPosition(renderer);
            background.renderSunCloud_Texture(renderer);

            trex.updatePhysic();
            trex.updateAnimation();
            trex.renderTrex_Texture(renderer);
            enemy.updateObjectPosition(renderer);

            score.update();
            score.render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }
}
