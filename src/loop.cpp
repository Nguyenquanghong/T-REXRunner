#include <loop.h>
#include <trex.h>
#include <enemy.h>
#include <background.h>
#include <data.h>
#include <iostream>
void rungame() {
    while (running) {
        if (enemy.checkCollision(trex.trexRect)) {
            isOver = true;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN && isOver == true) { 
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Tọa độ của nút restart (cần điều chỉnh theo UI)
                SDL_Rect restartButton = { (int)WINDOW_WIDTH / 2 - 25, (int)WINDOW_HEIGHT / 2 - 10, 50, 50 };

                // Kiểm tra xem chuột có nhấn vào nút restart không
                if (mouseX >= restartButton.x && mouseX <= (restartButton.x + restartButton.w) &&
                    mouseY >= restartButton.y && mouseY <= (restartButton.y + restartButton.h)) {
                    isOver = false;
                    trex.resetPosition();
                    background.resetPosition();
                    enemy.resetPosition();
                }
            } 
            else if (isOver == false) { 
                // Xử lý phím khi game chưa kết thúc
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_DOWN) trex.trexDucking();
                    if (event.key.keysym.sym == SDLK_UP) trex.trexJumping();
                }
                else if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.sym == SDLK_DOWN) trex.trexNormal();
                    if (event.key.keysym.sym == SDLK_UP) trex.trexJumping(); // Cần kiểm tra lại logic nhảy
                }
            }
        }

        // Vẽ màn hình
        SDL_RenderClear(renderer);
        
        if (isOver == true ) {
            background.renderOverGameBackground_Texture(renderer);
            background.renderRestartButton(renderer);
        } else {
            background.renderBackground_Texture(renderer);
            background.updateBackgroundPosition(renderer);

            trex.updatePhysic();
            trex.updateAnimation();
            trex.renderTrex_Texture(renderer);

            enemy.updateBirdAnimation();
            enemy.updateObjectPosition(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Giữ ~60 FPS
    }
}
