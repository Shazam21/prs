#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#pragma once


using namespace sf;

class Entity{
public:
    
    float x;
    float y;
    float w;
    float h;
    
    int nmb;
    int hp;
    int id;
    
    Texture txt;
    Sprite spr;
    
    int level;
    bool die;
public:
    
    void setPos(float X , float Y){
        x = X;
        y = Y;
    }
    
    void setSprPos(float x, float y) {
        this->spr.setPosition(x, y);
    }
    
    float getX() const { return this->x; }
    float getY() const { return this->y; }
    
    int getType() const { return this->nmb;}
    
    Sprite getSpr() { return this->spr; }
    
    void setHp(int exp){ this->hp = exp;}
    
    int getHp() const { return this->hp;}
    
    bool getDie() const { return this->die;}
    
    void Die() { this->die = true; }
    
    
    FloatRect getRect(){
        return FloatRect(x, y, w, h);
    }
    
    int getLevel() const { return this->level; }
    
    virtual void turn();
    
    ~Entity(){
        
    }
};
