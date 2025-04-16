#include <graphic.h>
#include <data.h>
#include <iostream>
#include <sstream>
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
    // sound
void loadSound(){
    jumpSound = Mix_LoadWAV("Data/sound/jump_sound.wav");
    dieSound = Mix_LoadWAV("Data/sound/die_sound.wav");
    scoreSound = Mix_LoadWAV("Data/sound/point_sound.wav");
    backgroundSound = Mix_LoadMUS("Data/sound/theme2_sound.wav");
}

//score

Score:: Score(){
    font = nullptr;
    value = 0;
    lastUpdate = SDL_GetTicks();
}
void Score::update() {
    Uint32 now = SDL_GetTicks();
    if (now - lastUpdate >= 100) {
        value++;
        lastUpdate = now;
    }
}

void Score::render(SDL_Renderer* renderer) {
    std::stringstream ss;
    ss.width(5);
    ss.fill('0');
    ss <<"SCORE: "<< value;
    SDL_Color color = {83, 83, 83, 255};
    
    font = TTF_OpenFont("fonts/arial.ttf", 24);
     // ---- THÊM KIỂM TRA LỖI NGAY TẠI ĐÂY ----
     if (font == nullptr) {
        SDL_Log("Không thể mở font để vẽ lỗi: %s", TTF_GetError());
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    if (surface == nullptr) { // Cũng nên kiểm tra lỗi ở đây
        SDL_Log("ERROR: Failed to create surface from text! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) { // Và kiểm tra lỗi ở đây nữa
        SDL_Log("ERROR: Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect destRect = {500, 10, surface->w , surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


