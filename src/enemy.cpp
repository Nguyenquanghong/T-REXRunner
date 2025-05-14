#include <enemy.h>
#include <data.h>
#include <graphic.h>

Enemy::Enemy() {
    birdFrame = 0;
    shibaFrame = 0;
    dogeFrame = 0;
    anhFrame = 0;
    shooterFrame = 0;
    birdLastFrameTime = SDL_GetTicks();
    shibaLastFrameTime = SDL_GetTicks();
    dogeLastFrameTime = SDL_GetTicks();
    anhLastFrameTime = SDL_GetTicks();
    lastBulletTime = SDL_GetTicks();
    shooterLastFrameTime = SDL_GetTicks();

    // mang kich thuoc + toa do cac enemy
    predefinedObjectSizes[0] = {0, 0, 35, 60};
    predefinedObjectSizes[1] = {0, 0, 45, 50};
    predefinedObjectSizes[2] = {0, 0, 50, 50};
    predefinedObjectSizes[3] = {0, 0, 30, 50};
    predefinedObjectSizes[4] = {0, 0, 55, 60};
    predefinedObjectSizes[5] = {0, 0, 50, 60};
    predefinedObjectSizes[6] = {0, 0, 50, 50};
    predefinedObjectSizes[7] = {0, 0, 90, 65};
    predefinedObjectSizes[8] = {0, 0, 75, 80};
    predefinedObjectSizes[9] = {0, 0, 65, 65};
    predefinedObjectSizes[10] = {0, 0, 40, 50};
    for (int i = 0; i < 11; i++) {
        objectRects[i].x = WINDOW_WIDTH;
        objectRects[i].y = BG_Y + (70 - predefinedObjectSizes[i].h);
        objectRects[i].w = predefinedObjectSizes[i].w;
        objectRects[i].h = predefinedObjectSizes[i].h;
    }
    objectRects[6].y = (rand() % 2 < 7) ? 200 : 240;
    bullet.active = false;
    bullet.speed = 13;
}

void Enemy::loadObjectTexture(SDL_Renderer* renderer) {
    objectTextures.push_back(loadTexture("Data/image/cactus/cactus-1.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/cactus-2.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/cactus-3.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/cactus-4.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/cactus-5.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/cactus-6.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/bird1.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/cheems.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/doge.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/anh.png", renderer));
    objectTextures.push_back(loadTexture("Data/image/cactus/shooter.png", renderer));
}

void Enemy::updateObjectPosition(SDL_Renderer* renderer) {
    float speed = SpeedController::getSpeed();
    objectRects[currentObjectIndex].x -= speed;

    if (objectRects[currentObjectIndex].x + objectRects[currentObjectIndex].w < 0) {
        currentObjectIndex = rand() % 11;
        objectRects[currentObjectIndex].x = WINDOW_WIDTH;

        if (currentObjectIndex == 6) { 
            objectRects[6].y = (rand() % 2) ? 190 : 250;
            birdMovingUp = (rand() % 2);
    }
}

    Uint32 currentTime = SDL_GetTicks();

    if (currentObjectIndex == 6) {
        if (currentTime > birdLastFrameTime + birdFrameDelay) {
            birdFrame = (birdFrame + 1) % 2;
            birdLastFrameTime = currentTime;
        }
          int moveSpeed = 1; 

        if (birdMovingUp) {
            objectRects[6].y -= moveSpeed;
            if (objectRects[6].y <= 190) {
                birdMovingUp = false; 
            }
        } else {
            objectRects[6].y += moveSpeed;
            if (objectRects[6].y >= 250) {
                birdMovingUp = true;
            }
        }
        SDL_Rect srcRect = { birdFrame * 84, 0, 84, 60 };
        SDL_RenderCopy(renderer, objectTextures[6], &srcRect, &objectRects[6]);
    } else if (currentObjectIndex == 7) {
        if (currentTime > shibaLastFrameTime + shibaFrameDelay) {
            shibaFrame = (shibaFrame + 1) % 2;
            shibaLastFrameTime = currentTime;
        }
        SDL_Rect srcRect = { 0, shibaFrame * 446, 1443, 446 };
        SDL_RenderCopy(renderer, objectTextures[7], &srcRect, &objectRects[7]);
    } else if (currentObjectIndex == 8) {
        if (currentTime > dogeLastFrameTime + dogeFrameDelay) {
            dogeFrame = (dogeFrame + 1) % 3;
            dogeLastFrameTime = currentTime;
        }
        SDL_Rect srcRect = { dogeFrame * 423, 0, 423, 427 };
        SDL_RenderCopy(renderer, objectTextures[8], &srcRect, &objectRects[8]);
    } else if (currentObjectIndex == 9) {
        if (currentTime > anhLastFrameTime + anhFrameDelay) {
            anhFrame = (anhFrame + 1) % 6;
            anhLastFrameTime = currentTime;
        }
        int frameWidth = 270, frameHeight = 295;
        int col = anhFrame % 3;
        int row = anhFrame / 3;
        SDL_Rect srcRect = { col * frameWidth, row * frameHeight, frameWidth, frameHeight };
        SDL_RenderCopyEx(renderer, objectTextures[9], &srcRect, &objectRects[9], 0, NULL, SDL_FLIP_HORIZONTAL);
    } else if (currentObjectIndex == 10) {
        if (currentTime > shooterLastFrameTime + shooterFrameDelay) {
            shooterFrame = (shooterFrame + 1) % 5
            ;
            anhLastFrameTime = currentTime;
        }
        int frameWidth = 245, frameHeight = 344;
        
        SDL_Rect srcRect = {    shooterFrame* frameWidth, 0, frameWidth, frameHeight };
        SDL_RenderCopyEx(renderer, objectTextures[10], &srcRect, &objectRects[10], 0, NULL, SDL_FLIP_HORIZONTAL);
        if (currentTime - lastBulletTime > bulletCooldown && !bullet.active) {
            bullet.rect = {objectRects[10].x, objectRects[10].y + objectRects[10].h / 2 - 5, 5, 5};
            bullet.active = true;
            lastBulletTime = currentTime;
        }
    } else {
        SDL_RenderCopy(renderer, objectTextures[currentObjectIndex], NULL, &objectRects[currentObjectIndex]);
    }

    if (bullet.active) {
        bullet.rect.x -= bullet.speed+SpeedController::getSpeed();
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &bullet.rect);
        if (bullet.rect.x + bullet.rect.w < 0) bullet.active = false;
        }
    } // xu li animation cho enemy

bool Enemy::checkCollision(const SDL_Rect& dinoRect) {
    SDL_Rect& enemyRect = objectRects[currentObjectIndex];
    bool enemyHit = (
        dinoRect.x < enemyRect.x + enemyRect.w &&
        dinoRect.x + dinoRect.w > enemyRect.x &&
        dinoRect.y < enemyRect.y + enemyRect.h &&
        dinoRect.y + dinoRect.h > enemyRect.y
    );
    bool bulletHit = false;
    if (bullet.active) {
        bulletHit = (
            dinoRect.x < bullet.rect.x + bullet.rect.w &&
            dinoRect.x + dinoRect.w > bullet.rect.x &&
            dinoRect.y < bullet.rect.y + bullet.rect.h &&
            dinoRect.y + dinoRect.h > bullet.rect.y
        );
    }
    return enemyHit || bulletHit;
}

bool Enemy::isEnemyOnScreen() {
    return objectRects[currentObjectIndex].x + objectRects[currentObjectIndex].w > 0 &&
           objectRects[currentObjectIndex].x < WINDOW_WIDTH;
}

void Enemy::resetPosition() {
    currentObjectIndex = rand() % 11;
    for (int i = 0; i < 11; i++) {
        objectRects[i].x = WINDOW_WIDTH;
        objectRects[i].y = BG_Y + (70 - predefinedObjectSizes[i].h);
    }
    objectRects[6].y = (rand() % 2) ? 200 : 240;
    bullet.active = false;
}

void Enemy::freeEnemy_Texture() {
    for (auto& tex : objectTextures) {
        SDL_DestroyTexture(tex);
    }
}
