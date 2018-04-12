
//
//  Player.cpp
//  prs
//
//  Created by Николай Костин on 18.03.18.
//  Copyright © 2018 Николай Костин. All rights reserved.
//

#include "Player.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Heal.hpp"
#include "SRTCT.hpp"
Player::Player(float XF, float YF ){
    this->hp = 100;
    this->score = 0;
    this->x = XF;
    this->y = YF;
    this->herotexture.loadFromFile("/Users/nikolajkostin/Desktop/na/na/Hero.png");
    this->herosprite.setTexture(herotexture);
    this->herosprite.setTextureRect(IntRect(70 , 0 , 86 ,160 ));
    this->herosprite.scale(0.5, 0.5);
    this->w = 20;
    this->h = 80;
    this->herosprite.setPosition(XF, YF);
    this->items.push_back("Book");
    this->items.push_back("Heal");
    this->level = 0;
    this->speed = 0;
    this->type = 0;
    this->font.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/sansation.ttf");
    this->attack = 20;
}
Player::Player(){
    this->herotexture.loadFromFile("/Users/nikolajkostin/Desktop/na/na/Hero.png");
    this->herosprite.setTexture(herotexture);
    this->herosprite.setTextureRect(IntRect(70 , 0 , 86 ,160 ));
    this->herosprite.scale(0.5, 0.5);
    
     this->font.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/sansation.ttf");
}

void Player::create(float x , float y){
    this->hp = 100;
    this->score = 0;
    this->x = x;
    this->y = y;
    this->w = 20;
    this->h = 80;
    this->herosprite.setPosition(x, y);
    this->items.push_back("Book");
    this->items.push_back("Heal");
    this->level = 0;
    this->speed = 0;
    this->type = 0;
   
    this->attack = 20;
}

void Player::turn(float x , float y){
    herosprite.move(x, y);
    this->x += x;
    this->y += y;
}


void Player::GUI(RenderWindow & window , std::vector <Entity*> ALL){
    std::stringstream ss;
    ss << this->hp;
    Text hp("", font , 30);
    std::string display = "HP " + ss.str();
    hp.setString(display);
    int n;
    if(this->findSome(ALL , window , n) == 1){
        PrintSome(window, "ENEMY IS NEAR", 100, 500 , Color::White);
    }
    
    
    hp.setPosition(700, 500);
    this->displayInt(window, this->level, 600, 500);
    window.draw(hp);
    
}
void Player::openInventory(RenderWindow & window , int selected ){
    window.clear();
    for(int i = 0 ; i < items.size() ; i++){
        
        if(i == selected){
            this->PrintSome(window, items[i], 25, 0.5 + i*30 , Color::Blue);
        }else{
            this->PrintSome(window, items[i], 25, 0.5 + i*30 , Color::White);
        }
      
        this->displayInt(window, i,1 , 0.5 + i * 30);
        
    }
    window.display();
}

void Player::interactionWithMap(std::vector<char**> levels ,
                                std::vector <Entity*> ALL)
{
    for (int i = y / 32; i < (y ) / 16 ;i++)
        for (int j = x / 32; j<(x ) / 16; j++)
        {
            
            if(x -1 < 55 ){
                x += 0.2;
            }
            if(y - 1 < 55 ){
                y += 0.2;
            }
            if(x + 1 > 640 ){
                x -= 0.2;
            }
            if(y +1 > 340 ){
                y -= 0.2;
            }
            
            
        }
}

void Player::update(float time){
    switch (dr) {
        case 0:
            dx = speed;
            dy = 0;
            break;
            
        case 1:
            dx = speed;
            dy = 0;
            break;
            
        case 2:
            dx = 0;
            dy = speed;
            break;
            
        case 3:
            dx = 0;
            dy = speed;
            break;
            
        default:
            
            break;
    }
    this->x +=dx * time;
    this->y +=dy * time;
    
    speed = 0;
    
    this->herosprite.setPosition(this->x, this->y);
    
}

void Player::inventory(RenderWindow & window ){
    
    if(Keyboard::isKeyPressed(Keyboard::I)){
        bool show = true;
        int selected = 0 ;
        Event event;
        while(show){
            this->openInventory(window , selected);
            
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                show = false;
            }
            while (window.pollEvent(event)) {
                if (event.key.code == Keyboard::W && event.type == Event::KeyReleased && selected > 0 ) {
                        selected--;
                }
                if (event.key.code == Keyboard::S && event.type == Event::KeyReleased && selected < items.size() - 1) {
                    
                    ++selected;
                }
                if (event.key.code == Keyboard::E && event.type == Event::KeyReleased) {
                    this->useItem(selected);
                }
                
            }
        }
    }//end of inventory loop
}

void Player::PrintSome(RenderWindow &  window ,std::string toPrint, float x ,float y , Color color){
    
    Text hp("", font , 30);
    hp.setString(toPrint);
    
    hp.setPosition(x, y);
    hp.setFillColor(color);
    window.draw(hp);
}

char** Player::makeLevel(){
    char ** arr = new char *[25];
    for (int i = 0; i < 25; i++) {
        arr[i] = new char[40];
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 40; j++) {
            if (i == 0 || j == 0 || j == 39 || i == 24) {
                arr[i][j] = '0';
            }
            else {
                arr[i][j] = ' ';
            }
        }
    }
    return arr;
}

void Player::levelControl(std::vector<char**> &levels, std::vector<Entity*> & ALL,
                          RenderWindow& window ) {
    
    int nmb ;
    if (this->findSome(ALL , window , nmb) == 0 ) {
        
        if (this->level < levels.size() && this->level + 1 != levels.size()) {
            this->level++;
        }
        
        if (this->level == levels.size() - 1) {
            levels.emplace_back(this->makeLevel());
            this->level++;
            this->x = 60;
            this->y = 60;
            ALL.emplace_back(new Enter((rand() & 50) + 100, (rand() & 50) + 100, this->level));
            ALL.emplace_back(new Place((rand() & 51) + 100, (rand() & 51) + 100, 2, this->level));
            
        }
        
        
    }
    
    if (this->findSome(ALL , window ,nmb) == 2) {
        if (this->level > 0) {
            this->level--;
            this->x = 60;
            this->y = 60;
        }
        
    }
    
}

int Player::findSome(std::vector<Entity *> ALL , RenderWindow & window , int &nmb){
    int found = -2;

    for(int i = 0 ; i < ALL.size(); i++){
        if(this->getRect().intersects(ALL[i]->getRect()) && ALL[i]->getLevel() == this->level){
            found = ALL[i]->getType();
            nmb = i;
        }
    }
    
    
    return found;
}
void Player::savePlayer(std::string filepath){
    std::ofstream file(filepath);
    if(!file.is_open()){
        std::cout << "File cant be open" << std::endl;
    }
    std::stringstream ss[10];
    
    ss[0] << this->x;
    ss[1] << this->y;
    ss[2] << this->level;
    ss[3] << this->hp;
    
    file << "PLAYER" << std::endl;
    file << ss[0].str() << std::endl;//x
    file << ss[1].str() << std::endl;//y
    file << ss[2].str() << std::endl;//w
    file << ss[3].str() << std::endl;//hp
    
    
    
    file.close();
}
void Player::load(){
    
}





