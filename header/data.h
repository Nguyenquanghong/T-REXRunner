#ifndef DATA_H
#define DATA_H
#include <iostream> 
#include <SDL2/SDL.h>
//kich thuoc window
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;

//loop
     bool running = true;

//background map
    const int BG_SPEED = 4;
    int BG_X = 0;
    const int BG_Y = 400;
    const int BG_HEIGHT = 200;
    const int BG_WIDTH = 800;
//khai bao moi truong vat ly
    const double JUMP_FORCE = -12;
    const double GRAVITY = 0.5;
//Trex
    struct Trex{
        SDL_Rect trexRect;
        float velocityY;
        bool isDucking;
        bool isJumping;
        bool fastFall;

        Trex(){
            trexRect= {20, 445, 50, 50};
            isDucking = false;
            isJumping = false;
            fastFall = false;
            velocityY = 0;
        }
        bool onGround() {
            return trexRect.y >= 445; // Kiểm tra nếu khủng long chạm đất
        }
        
        void trexNormal(){
            trexRect= {20, 445, 50, 50};
            isDucking = false;
           
        }
        void trexDucking(){
            if(onGround()){
                trexRect ={20, 465, 60, 35};
                isDucking = true;
            }
            else if(isJumping){
                fastFall = true;
            }
        }
        void trexJumping() {
            if (!isJumping&&!isDucking) { // Chỉ nhảy khi đứng trên mặt đất
                isJumping = true;
                velocityY = JUMP_FORCE;
            }
        }
        void updatePhysic() {
            if (isJumping) {
                trexRect.y += velocityY;  // Cập nhật vị trí
                velocityY += fastFall ? GRAVITY*4 : GRAVITY; // Ảnh hưởng của trọng lực
    
                // Chạm đất
                if (trexRect.y >= 445) {
                    trexRect.y = 445;
                    isJumping = false;
                    velocityY = 0;
                    fastFall = false;
                }
            }
        }
    };
// khai báo nhân vật chính
    Trex mainCharacter;
    
#endif