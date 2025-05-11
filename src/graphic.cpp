#include <graphic.h>
#include <data.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

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

// sound
void loadSound(){
    jumpSound = Mix_LoadWAV("Data/sound/jump_sound.wav");
    dieSound = Mix_LoadWAV("Data/sound/die_sound.wav");
    scoreSound = Mix_LoadWAV("Data/sound/point_sound.wav");
    backgroundSound = Mix_LoadMUS("Data/sound/theme2_sound.wav");
    click =  Mix_LoadWAV("Data/sound/click.mp3");
}

// Score
Score::Score(){
    font = nullptr;
    value = 0;
    lastUpdate = SDL_GetTicks();
    highScores = {0, 0, 0, 0};
    loadHighScore();
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
    ss <<"score:"<< value;
    SDL_Color color = {83, 83, 83, 255};

    font = TTF_OpenFont("fonts/pixel.ttf",13);
    if (font == nullptr) {
        SDL_Log("Không thể mở font để vẽ lỗi: %s", TTF_GetError());
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    if (surface == nullptr) {
        SDL_Log("ERROR: Failed to create surface from text! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        SDL_Log("ERROR: Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    SDL_Rect destRect = {400, 5, surface->w , surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


void Score::renderHighScore(SDL_Renderer* renderer) {
    SDL_Color color = {83, 83, 83, 255};
    font = TTF_OpenFont("fonts/arial.ttf", 24);
    if (!font) return;

    int baseX = 215;  // X-position aligned with green boxes
    int baseY = 90;   // Starting Y-position based on image layout
    int boxHeight = 60; // Space between each box (box height + margin)

    for (int i = 0; i < 4 && i < highScores.size(); ++i) {
        std::stringstream ss;
        ss <<"Top"<<i+1<<": "<< highScores[i];

        SDL_Surface* surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
        if (!surface) continue;

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_FreeSurface(surface);
            continue;
        }

        int textW = surface->w;
        int textH = surface->h;
        SDL_Rect destRect = {baseX + (135 - textW) / 2, baseY + i * boxHeight + (49 - textH) / 2, textW, textH};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}


void Score::loadHighScore() {
    std::ifstream file("highscore.txt");
    highScores.clear();
    int s;
    while (file >> s) {
        highScores.push_back(s);
    }
    while (highScores.size() < 4) highScores.push_back(0);
    std::sort(highScores.begin(), highScores.end(), std::greater<int>());
}

void Score::saveHighScore() {
    highScores.push_back(value);
    std::sort(highScores.begin(), highScores.end(), std::greater<int>());
    if (highScores.size() > 4) highScores.resize(4);
    std::ofstream file("highscore.txt");
    for (int s : highScores) file << s << "\n";
}

float SpeedController::baseSpeed = 4.0f;
float SpeedController::speedMultiplier = 1.0f;
Uint32 SpeedController::lastUpdateTime = 0;

void SpeedController::updateSpeed(bool noEnemiesOnScreen) {
    Uint32 currentTime = SDL_GetTicks();

    if (noEnemiesOnScreen && currentTime > lastUpdateTime + 5000) {
        speedMultiplier += 0.1f;
        lastUpdateTime = currentTime;
    }
}

float SpeedController::getSpeed(){
    return baseSpeed * speedMultiplier;
}

void SpeedController::resetSpeed(){
    baseSpeed = 4.0f;
    speedMultiplier = 1.0f;
    lastUpdateTime = SDL_GetTicks();
}
