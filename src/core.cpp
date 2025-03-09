#include <core.h>
#include <data.h>
    bool InitSDL(SDL_Window*& window, SDL_Renderer*& renderer){
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
                                  WINDOW_WIDTH,WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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
    void CloseSDL(SDL_Window* window, SDL_Renderer* renderer){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    