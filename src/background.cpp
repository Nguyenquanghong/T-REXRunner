#include <background.h>
#include <graphic.h>
#include <data.h>

void Background:: loadBackground_Texture(SDL_Renderer* renderer){
    bgColor = loadTexture("Data/image/background/blue.png",renderer);

    bgTextures.push_back(loadTexture("Data/image/background/ground_1.png",renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_2.png", renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_3.png", renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_4.png", renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_5.jpg", renderer));
    startGameBg = loadTexture("Data/image/background/start.png",renderer);
    overGameBg = loadTexture("Data/image/background/Gameover.png",renderer);

    restartButton = loadTexture("Data/image/background/replay.png",renderer);
}

void Background:: renderBackground_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,bgColor,NULL,NULL);
}
void Background::updateBackgroundPosition(SDL_Renderer* renderer) {

    // Cập nhật vị trí nền theo thời gian thực
    BG_X -= BG_SPEED  ;

    // Nếu ảnh đầu tiên chạy ra khỏi màn hình, đưa nó về cuối danh sách
    if (BG_X <= -WINDOW_WIDTH) {
        SDL_Texture* firstTexture = bgTextures.front();
        bgTextures.erase(bgTextures.begin());
        bgTextures.push_back(firstTexture);
        BG_X += WINDOW_WIDTH; // Duy trì vị trí chính xác
    }

    // Vẽ background theo thứ tự trong danh sách
    int numberOfBackgrounds = bgTextures.size();
    for (int i = 0; i < numberOfBackgrounds; i++) {
        SDL_Rect dstRect = {static_cast<int>(BG_X + i * WINDOW_WIDTH), BG_Y, BG_WIDTH, BG_HEIGHT};
        SDL_RenderCopy(renderer, bgTextures[i], NULL, &dstRect);
    }
}
void Background:: resetPosition(){
    BG_X = 0;
}
void Background:: renderStartGameBackground_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,startGameBg,NULL,NULL);

}
void Background:: renderOverGameBackground_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,overGameBg,NULL,NULL);

}
void Background:: renderRestartButton(SDL_Renderer* renderer){
    SDL_Rect replayButton ={(int)WINDOW_WIDTH/2 -25, WINDOW_HEIGHT/2 -10, 50, 50};
    SDL_RenderCopy(renderer, restartButton, NULL, &replayButton);
}

void Background:: freeBackground_Texture(){
    for (auto texture : bgTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(bgColor);
    SDL_DestroyTexture(startGameBg);
    SDL_DestroyTexture( overGameBg);
    SDL_DestroyTexture( restartButton);
}
