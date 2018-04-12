#pragma once
#include "Player.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


class Enemy : public Entity{

private:
    
    
    
    void renderFightField(Sprite map ,RenderWindow& window){
        
        for(int i = 0 ; i < 10 ; i++ ){
            for(int j = 0 ; j < 10 ; j++){
                
            }
        }
    }
    
    
    
public:
    Enemy(float X, float Y , int LVL);
    
    void turn();
    
    void kill(){
        
    }
};
