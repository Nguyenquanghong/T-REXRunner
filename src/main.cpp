
#include <commonfunc.h>


int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Khởi tạo SDL
    if (!initSDL(window, renderer,WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return -1;  // Thoát nếu lỗi
    }
    
    // background đứng yên
    SDL_Texture* bgColor = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/blue.png",renderer);

    //background di chuyển
    vector<SDL_Texture*> bgTextures;
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_1.png",renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_2.png", renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_3.png", renderer));
    bgTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/background/ground_4.png", renderer));
    
    // T-rex
    SDL_Texture* trex_run_1 = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_run_1.png",renderer);
    // SDL_Texture* trex_run_2= loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_run_2.png",renderer);
    SDL_Texture* trex_bow = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_bow_1.png",renderer);
    SDL_Texture* trex_jump = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/t-rex/dino_jump.png",renderer);
    // Vòng lặp game
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            else if(event.type== SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_DOWN) mainCharacter.trexDucking();
                if(event.key.keysym.sym == SDLK_UP) mainCharacter.trexJumping();
            }
            else if(event.type == SDL_KEYUP) {
                if(event.key.keysym.sym == SDLK_DOWN) mainCharacter.trexNormal();
                if(event.key.keysym.sym == SDLK_UP)  mainCharacter.trexJumping();
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_DOWN) {
                    mainCharacter.trexNormal();
                }
            }
        }
        mainCharacter.updatePhysic();

        SDL_RenderClear(renderer);
        //back ground nền đứng yên
        SDL_RenderCopy(renderer,bgColor,NULL,NULL);

        // Cập nhật và vẽ background di chuyen
        updateBackground(renderer, bgTextures, BG_X);

        renderTrex(renderer,trex_run_1,trex_jump,trex_bow,mainCharacter);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Giữ ~60 FPS
    }


    // Giải phóng tài nguyên
    close(window, renderer, bgTextures);

    return 0;
    
}
