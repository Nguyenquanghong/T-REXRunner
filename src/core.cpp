#include <core.h>
#include <data.h>
    bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "Lỗi SDL: " << SDL_GetError() << std::endl;
            return false;
        }
    
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cerr << "Lỗi SDL_image: " << IMG_GetError() << std::endl;
            return false;
        }
    
        window = SDL_CreateWindow("Game Window",
                                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Lỗi tạo cửa sổ: " << SDL_GetError() << std::endl;
            return false;
        }
    
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            std::cerr << "Lỗi tạo renderer: " << SDL_GetError() << std::endl;
            return false;
        }
    
        return true;
    }
    bool InitMixer() {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,  8192) < 0) {
            std::cerr << "Lỗi khởi tạo SDL_mixer: " << Mix_GetError() << std::endl;
            return false;
        }
        if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
            std::cerr << "Lỗi khởi tạo định dạng SDL_mixer: " << Mix_GetError() << std::endl;
            return false;
        }
        return true; 
    }

    void CloseSDL(SDL_Window* window, SDL_Renderer* renderer){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    void CloseMixer(){
        Mix_CloseAudio(); 
        Mix_Quit();    
    }
