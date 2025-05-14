#include <background.h>
#include <graphic.h>
#include <data.h>

void Background:: loadBackground_Texture(SDL_Renderer* renderer){
    bgColor = loadTexture("Data/image/background/blue.png",renderer);
    cloud = loadTexture("Data/image/background/cloud.png",renderer);
    sun = loadTexture("Data/image/background/sun.png",renderer);
    bgTextures.push_back(loadTexture("Data/image/background/ground_1.png",renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_2.png", renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_3.png", renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_4.png", renderer));
    bgTextures.push_back(loadTexture("Data/image/background/ground_5.jpg", renderer));
    startGameBg = loadTexture("Data/image/background/startbackground.png",renderer);
    overGameBg = loadTexture("Data/image/background/Gameover.png",renderer);
    pauseGameBg = loadTexture("Data/image/background/pausebackground.png",renderer);
    pause_icon = loadTexture("Data/image/background/pause.png",renderer);
    pause_icon2 = loadTexture("Data/image/background/pause_icon.png",renderer);
    highScoreGameBg = loadTexture("Data/image/background/highscoreranking.png",renderer);
}

void Background:: renderBackground_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,bgColor,NULL,NULL);
}
void Background :: renderSunCloud_Texture(SDL_Renderer* renderer){
    SDL_Rect rectSun = {300,50,50,50};
    SDL_RenderCopy(renderer, sun, NULL, &rectSun);
    cloud_x-= cloud_speed;
    if(cloud_x <= -(WINDOW_WIDTH+70)){
        cloud_x = WINDOW_WIDTH;
    }
    SDL_Rect rectCloud = {cloud_x,70,70,25};
    SDL_RenderCopy(renderer, cloud, NULL, &rectCloud);
    SDL_Rect rectPause = {370,5,20,10};
    SDL_RenderCopy(renderer, pause_icon, NULL, &rectPause);
}
void Background::updateBackgroundPosition(SDL_Renderer* renderer) {
    BG_X -= SpeedController::getSpeed(); 
    if (BG_X <= -WINDOW_WIDTH) {
        SDL_Texture* firstTexture = bgTextures.front();
        bgTextures.erase(bgTextures.begin());
        bgTextures.push_back(firstTexture);
        BG_X += WINDOW_WIDTH; 
    }

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
void Background:: renderPauseGameBackground_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,pauseGameBg,NULL,NULL);
 
}
void Background:: renderHighScore_Texture(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,highScoreGameBg,NULL,NULL);
 
}
void Background:: renderPause_Texture(SDL_Renderer* renderer){
    SDL_Rect rectPause = {250,150,50,50};
    SDL_RenderCopy(renderer, pause_icon2,NULL,&rectPause);
}
void Background:: freeBackground_Texture(){
    for (auto texture : bgTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(sun);
    SDL_DestroyTexture(cloud);
    SDL_DestroyTexture(bgColor);
    SDL_DestroyTexture(startGameBg);
    SDL_DestroyTexture( overGameBg);
    SDL_DestroyTexture(pause_icon);
}
