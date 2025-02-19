#ifndef COMMONFUNC_H
#define COMMONFUNC_H
#include <data.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
using namespace std;


bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Lỗi SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // Khởi tạo SDL_image (hỗ trợ PNG, JPG)
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Lỗi SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    // Tạo cửa sổ
    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Lỗi tạo cửa sổ: " << SDL_GetError() << std::endl;
        return false;
    }

    // Tạo Renderer với Hardware Acceleration (tăng hiệu suất)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Lỗi tạo renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true; // Thành công
}



// Hàm tải ảnh vào SDL_Texture
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        cout << "Lỗi tải ảnh: " << path << " - " << IMG_GetError() << endl;
        return nullptr;
    }
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

// Hàm xử lý background chạy liên tục
void updateBackground(SDL_Renderer* renderer, vector<SDL_Texture*>& bgTextures, int& bgX) {
    // Di chuyển nền sang trái
    bgX -= BG_SPEED;

    // Nếu ảnh đầu tiên chạy ra khỏi màn hình, đưa nó về cuối danh sách
    if (bgX <= -WINDOW_WIDTH) {
        SDL_Texture* firstTexture = bgTextures.front();
        bgTextures.erase(bgTextures.begin());
        bgTextures.push_back(firstTexture);
        bgX = 0;  // Reset vị trí
    }

    // Vẽ background theo thứ tự trong danh sách
    int numberOfBackgrounds = bgTextures.size();
    for (int i = 0; i < numberOfBackgrounds; i++) {
        SDL_Rect dstRect = {bgX + (i * WINDOW_WIDTH), BG_Y, BG_WIDTH,BG_HEIGHT};
        SDL_RenderCopy(renderer, bgTextures[i], NULL, &dstRect);
    }
}




// Hàm giải phóng tài nguyên
void close(SDL_Window* window, SDL_Renderer* renderer, vector<SDL_Texture*>& bgTextures) {
    for (auto texture : bgTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif