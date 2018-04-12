#include "Entity.hpp"
#include <vector>

class Place : public Entity{
    
    
public:
    Place(float X , float Y , int c , int LVL){
        this->x = X;
        this->y = Y;
        this->w = 16;
        this->h = 16;
        this->nmb = c;
        this->hp = 100;
        this->level = LVL;
        this->txt.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/Heart.png");
        this->spr.setTexture(this->txt);
        this->spr.setTextureRect(IntRect(0 , 0 , w , h));
        this->spr.setPosition(x , y);
        this->die = false;
    }
  
    
    
    
};
