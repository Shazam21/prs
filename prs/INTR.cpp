//
//  INTR.cpp
//  prs
//
//  Created by Николай Костин on 09.03.18.
//  Copyright © 2018 Николай Костин. All rights reserved.
//

#include "INTR.hpp"

//
//  Interference.cpp
//  simple
//
//  Created by Николай Костин on 08.03.18.
//  Copyright © 2018 Николай Костин. All rights reserved.
//


#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int HM = 25;






void PrepareMap(String TileMap[] , const int size , Sprite & map ,Window & window){
    
    for(int i = 0; i < size ; i++){
        for(int j = 0 ; j < size; j++){
            if(i == 0 || i == size-1 || j == 0 || j == size-1){
                TileMap[i][j] = '0';
            }else{
                TileMap[i][j] = ' ';
            }
        }
    }
    
    
    Image mapImg;
    mapImg.loadFromFile("Hero.png");
    Texture mapT;
    mapT.loadFromImage(mapImg);
    
    map.setTexture(mapT);
    
    
    
}



class Player{
    int x;
    int y;
    int toX;
    int toY;
    int hp;
    int level;
    int count;
    char cymbol;
    int attack;
    int tempX;
    int tempY;
    int Killed;
    int Collected;
    int progress;
    int armor;
    float XF;
    float YF;
    
    Sprite herosprite;
    Texture herotexture;
    char GUI[10][80];
public:
    
    Player(float XFF , float YFF ){
        
        herotexture.loadFromFile("/Users/nikolajkostin/Desktop/simple/simple/en.lproj/Hero.png");
        herosprite.setTexture(herotexture);
        herosprite.setTextureRect(IntRect(0, 0 ,140 , 200));
        herosprite.setPosition(100 , 100);
        
        this->XF = XFF;
        this->YF = YFF;
        this-> Killed = 0;
        this->Collected = 0;
        this->level = 0 ;
        this->cymbol = 'P';
        this->progress = 0;
        this->attack = 50;
        this->count = 0;
        this->hp = 100;
        this->armor = 0;
    }
    
    void turn(char ** arr, int toX, int toY) {
        if (arr[toX][toY] == ' ') {
            arr[this->x][this->y] = ' ';
            this->x = toX;
            this->y = toY;
            arr[this->x][this->y] = 'P';
            this->toX = toX;
            this->toY = toX;
        }else if(arr[toX][toY] == '#'){
            this->hp -=5;
        }
    }
    Sprite getSprite(){
        return this->herosprite;
    }
    
    void move(float x , float y){
        this->XF += x;
        this->YF += y;
        this->herosprite.move(x, y);
    }
    char getCymbol() const { return this->cymbol; }
    
    int getX() const { return this->x; }
    int getY() const { return this->y; }
    
    int getLevel() const { return this->level; }
    
    void setX(int exp)  { this->x = exp; }
    void setY(int exp)  { this->y = exp; }
    
    void settoX(int exp) { this->toX = exp; }
    void settoY(int exp) { this->toY = exp; }
    
    int getTX() { return this->tempX; }
    int getTY() { return this->tempY; }
    
    int getAttack(){ return this->attack;}
    
    int gettoX() const { return this->toX; }
    int gettoY() const { return this->toY; }
    
    int getHp() const { return this->hp;}
    
    void setHp(int exp) { this->hp = exp; }
    
    bool SEE( vector<char ** > &MAPS , char smb){
        int SX = this->x;
        int SY = this->y;
        
        if(MAPS[this->level][SX + 1][SY] == smb){
            this->tempX = SX + 1;
            this->tempY = SY ;
            return true;
        }
        if(MAPS[this->level][SX][SY + 1] == smb){
            this->tempX = SX ;
            this->tempY = SY + 1;
            return true;
        }
        if(MAPS[this->level][SX - 1][SY] == smb){
            this->tempX = SX - 1;
            this->tempY = SY ;
            return true;
        }
        if(MAPS[this->level][SX][SY - 1] == smb){
            this->tempX = SX ;
            this->tempY = SY - 1 ;
            return true;
        }
        return false;
    }
};
