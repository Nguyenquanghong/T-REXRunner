#include <background.h>
#include <graphic.h>
#include <data.h>

void Background:: loadBackground_Texture(SDL_Renderer* renderer){
    bgColor = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/blue.png",renderer);

    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_1.png",renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_2.png", renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_3.png", renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_4.png", renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_5.jpg", renderer));
}

void Background:: renderBackground_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,bgColor,NULL,NULL);
}
void Background::updateBackgroundPosition(SDL_Renderer* renderer) {

    // Cập nhật vị trí nền theo thời gian thực
    BG_X -= BG_SPEED * GameManager::speedMultiplier;

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

void Background:: freeBackground_Texture(){
    for (auto texture : bgTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(bgColor);
}
