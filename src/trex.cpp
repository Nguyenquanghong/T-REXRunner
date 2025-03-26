#include <trex.h>
#include <graphic.h>
#include <data.h>

Trex::Trex(){

    trexRect= {TREX_X,TREX_Y, TREX_WIDTH, TREX_HEIGHT};
    isDucking = false;
    isJumping = false;
    fastFall = false;
    velocityY = 0;
    currentFrame = 0;
    frameDelay = 100; // Đổi frame sau mỗi 100ms
    lastFrameTime = SDL_GetTicks();
}

void  Trex:: loadTrex_Texture(SDL_Renderer* renderer){
    trex_run[0] = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_run_1.png",renderer);
    trex_run[1] = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_run_2.png",renderer);
    trex_bow[0] = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_bow_1.png",renderer);
    trex_bow[1] = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_bow_2.png",renderer);
    trex_jump = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_jump.png",renderer);
    if (!trex_run[0]|| !trex_run[1] || !trex_bow[0] || !trex_bow[1]|| !trex_jump) {
        std::cerr << "Failed to load Trex textures: " << SDL_GetError() << std::endl;
    }
}

void Trex:: renderTrex_Texture(SDL_Renderer* renderer){
    if (isJumping) {
        SDL_RenderCopy(renderer,trex_jump, NULL,&trexRect);
    } 
    else if (isDucking) {
        SDL_RenderCopy(renderer,trex_bow[currentFrame], NULL, &trexRect);
    } 
    else {
        SDL_RenderCopy(renderer,trex_run[currentFrame], NULL, &trexRect);
    }
}

void Trex::updateAnimation() {
    Uint32 currentTime = SDL_GetTicks(); // Lấy thời gian hiện tại

    // Nếu đủ thời gian delay thì đổi frame
    if (currentTime > lastFrameTime + frameDelay) {
        currentFrame = (currentFrame + 1) % 2; // Chuyển đổi giữa 2 frame chạy
        lastFrameTime = currentTime;
    }
}

bool Trex:: onGround(){
    return trexRect.y >=TREX_Y ;
}

void Trex:: trexNormal(){
    trexRect= {TREX_X,TREX_Y, TREX_WIDTH, TREX_HEIGHT};
    isDucking = false;
   
}

void Trex:: trexDucking(){
    if(onGround()){
        trexRect ={TREX_X,TREX_Y+15, TREX_WIDTH+5 , TREX_HEIGHT-15};
        isDucking = true;
    }
    else if(isJumping){
        fastFall = true;
    }
}

void Trex:: trexJumping(){
    if (!isJumping&&!isDucking) { // Chỉ nhảy khi đứng trên mặt đất
        isJumping = true;
        velocityY = JUMP_FORCE;
        Mix_PlayChannel(-1, jumpSound, 0);
    }
}

void Trex:: updatePhysic(){
    if (isJumping) {
        trexRect.y += velocityY;  // Cập nhật vị trí
        velocityY += fastFall ? GRAVITY*4 : GRAVITY; // Ảnh hưởng của trọng lực
        // Chạm đất
        if (onGround()) {
            trexRect.y =TREX_Y;
            isJumping = false;
            velocityY = 0;
            fastFall = false;
        }
    }
}
void Trex:: loadTrexSounds(){
    jumpSound = Mix_LoadWAV("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/sound/jump_sound.wav");
    dieSound = Mix_LoadWAV("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/sound/die_sound.wav");
    scoreSound = Mix_LoadWAV("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/sound/point_sound.wav");

}
void Trex:: resetPosition(){
    trexRect = {TREX_X, TREX_Y, TREX_WIDTH, TREX_HEIGHT}; // Reset vị trí ban đầu
    isDucking = false;
    isJumping = false;
    fastFall = false;
    velocityY = 0;
    currentFrame = 0;
    
}

void Trex:: freeTrex_Texture(){
    SDL_DestroyTexture(trex_run[0]);
    SDL_DestroyTexture(trex_run[1]);
    SDL_DestroyTexture(trex_jump);
    SDL_DestroyTexture(trex_bow[0]);
    SDL_DestroyTexture(trex_bow[1]);
}