#include "Enemy.hpp"

using namespace sf;

Enemy::Enemy(float X , float Y , int lvl){
    this->x = X;
    this->y = Y;
    this->h = 16.0f;
    this->w = 16.0f;
    this->nmb = 1;
    this->hp = 100;
    this->level = lvl;
    
    this->txt.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/Stone.png");
    this->spr.setTexture(this->txt);
    this->spr.setTextureRect(IntRect(0 , 0 , 16 , 16));
    this->spr.setPosition(x , y);
    this->die = false;
}
void Enemy::turn(){
    if((rand() & 1) == 0 ){
        this->spr.setPosition(x + 0.1, y);
    }else{
         this->spr.setPosition(x , y+ 0.1);
    }
}

