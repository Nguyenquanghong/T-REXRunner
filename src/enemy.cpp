#include <enemy.h>
#include <data.h>
#include <graphic.h>

//Bird
    Enemy:: Enemy(){
        currentFrame = 0;
        frameDelay = 80; // Đổi frame sau mỗi 100ms
        lastFrameTime = SDL_GetTicks();
        speed = 4.0f;

        isBirdActive = true;
        birdRect.x = WINDOW_WIDTH - 50;  // Bird xuất hiện ngoài màn hình
        birdRect.y = (rand() % 2 == 0) ? 300 : 400;  // Random vị trí cao hoặc thấp
        birdRect.w = 50;  // Chiều rộng Bird
        birdRect.h = 40;  // Chiều cao Bird
        
        predefinedCactusSizes[0] = {0, 0, 40, 60};  // Cactus 1
        predefinedCactusSizes[1] = {0, 0, 45, 50};  // Cactus 2
        predefinedCactusSizes[2] = {0, 0, 50, 50};  // Cactus 3
        predefinedCactusSizes[3] = {0, 0, 50, 50};  // Cactus 4
        predefinedCactusSizes[4] = {0, 0, 55, 50};  // Cactus 5
        predefinedCactusSizes[5] = {0, 0, 50, 60};  // Cactus 6
    
        
        for (int i = 0; i < 6; i++) {
            objectRects[i].x = WINDOW_WIDTH;
            objectRects[i].y = BG_Y + (80 - predefinedCactusSizes[i].h);
            objectRects[i].w = predefinedCactusSizes[i].w;
            objectRects[i].h = predefinedCactusSizes[i].h;
        }
    }


    void Enemy:: loadObjectTexture(SDL_Renderer* renderer){
        bird[0] = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/bird/bird-1.png",renderer);
        bird[1] = loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/bird/bird-2.png",renderer);
        objectTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/cactus/cactus-1.png",renderer));
        objectTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/cactus/cactus-2.png",renderer));
        objectTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/cactus/cactus-3.png",renderer));
        objectTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/cactus/cactus-4.png",renderer));
        objectTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/cactus/cactus-5.png",renderer));
        objectTextures.push_back(loadTexture("C:/Users/Quang Hong/Desktop/T-REXRunner/Data/image/cactus/cactus-6.png",renderer));
        
    }
    void Enemy::updateObjectPosition(SDL_Renderer* renderer) {
        if (isBirdActive) {
            // Bird di chuyển
            birdRect.x -= speed;
    
            // Nếu Bird rời khỏi màn hình
            if (birdRect.x + birdRect.w < 0) {
                isBirdActive = false;  // Chuyển sang Cactus
                cactusCounter = 0;  // Reset bộ đếm Cactus
                currentObjectIndex = rand() % 6;  // Chọn Cactus ngẫu nhiên
                objectRects[currentObjectIndex].x = WINDOW_WIDTH;
            }
    
            // Render Bird
            SDL_RenderCopy(renderer, bird[currentFrame], NULL, &birdRect);
        } else {
            // Cactus di chuyển
            objectRects[currentObjectIndex].x -= speed * GameManager::speedMultiplier;
    
            // Nếu Cactus rời khỏi màn hình, reset vị trí và chọn Cactus mới
            if (objectRects[currentObjectIndex].x + objectRects[currentObjectIndex].w < 0) {
                cactusCounter++;  // Tăng bộ đếm Cactus
                if (cactusCounter < 6) {
                    // Tiếp tục chọn Cactus mới
                    currentObjectIndex = rand() % 6;
                    objectRects[currentObjectIndex].x = WINDOW_WIDTH;
                } else {
                    // Sau khi hiển thị 6 Cactus, quay lại Bird
                    isBirdActive = true;
                    birdRect.x = WINDOW_WIDTH;
                    birdRect.y = (rand() % 2 == 0) ? 300 : 400;
                }
            }
    
            //  Render Cactus
            SDL_RenderCopy(renderer, objectTextures[currentObjectIndex], NULL, &objectRects[currentObjectIndex]);
        }
    }
    
    
    void Enemy:: updateBirdAnimation(){
            Uint32 currentTime = SDL_GetTicks(); // Lấy thời gian hiện tại
        
            // Nếu đủ thời gian delay thì đổi frame
            if (currentTime > lastFrameTime + frameDelay) {
                currentFrame = (currentFrame + 1) % 2; // Chuyển đổi giữa 2 frame chạy
                lastFrameTime = currentTime;
        }
        
    }

    bool Enemy::checkCollision(const SDL_Rect& dinoRect) {
        SDL_Rect enemyRect = isBirdActive ? birdRect : objectRects[currentObjectIndex];
    
        return (dinoRect.x < enemyRect.x + enemyRect.w &&
                dinoRect.x + dinoRect.w > enemyRect.x &&
                dinoRect.y < enemyRect.y + enemyRect.h &&
                dinoRect.y + dinoRect.h > enemyRect.y);
    }

    void Enemy:: resetPosition(){
            // Đặt lại Bird về vị trí ban đầu
            isBirdActive = true;
            birdRect.x = WINDOW_WIDTH - 50;
            birdRect.y = (rand() % 2 == 0) ? 120 : 250;
            
            // Đặt lại vị trí của các Cactus
            for (int i = 0; i < 6; i++) {
                objectRects[i].x = WINDOW_WIDTH;
                objectRects[i].y = BG_Y + (80 - predefinedCactusSizes[i].h);
            }
            
            cactusCounter = 0;
            currentObjectIndex = 0;
        

    }

     void Enemy :: freeObject_Texture(){
        SDL_DestroyTexture(bird[0]);
        SDL_DestroyTexture(bird[1]);
     }
