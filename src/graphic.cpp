#include <graphic.h>
#include <iostream>

// Hàm tải ảnh vào SDL_Texture
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
       std:: cout << "Lỗi tải ảnh: " << path << " - " << IMG_GetError() << std:: endl;
        return nullptr;
    }
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

    float GameManager::speedMultiplier = 1.0f;
    Uint32 GameManager::lastUpdateTime = 0;
    
    //  Hàm cập nhật tốc độ game
    void GameManager::updateSpeed() {
        Uint32 currentTime = SDL_GetTicks();  // Lấy thời gian hiện tại
        
        if (currentTime > lastUpdateTime + 5000) { // Cứ 5 giây tăng tốc độ
            speedMultiplier += 0.1f; // Tăng 10% tốc độ
            lastUpdateTime = currentTime;
        }
    }