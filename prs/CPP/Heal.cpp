//
//  Heal.cpp
//  prs
//
//  Created by Николай Костин on 10.03.18.
//  Copyright © 2018 Николай Костин. All rights reserved.
//

#include "Heal.hpp"


Enter::Enter(float X , float Y ,int lvl){
    this->x = X;
    this->y = Y;
    this->hp = 100;
    this->w = 16;
    this->h = 16;
    this->nmb = 0;
    this->level = lvl;
    this->txt.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/Sprites.png");
    this->spr.setTexture(this->txt);
    this->spr.setTextureRect(IntRect(16 , 0 , w , h));
    this->spr.setPosition(this->x, this->y);
    this->die = false;
}



