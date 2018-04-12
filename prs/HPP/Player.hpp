#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#pragma once
#include "Entity.hpp"

using namespace sf;

class Player{
    
    int hp ;
    int score;
    int attack;
    int armor;
    int dr;
    
    int level;
    int type;
    int money;
    
    float x;
    float y;
    float w;
    float h;
    
    float dx;
    float dy;
    float speed;
    
    Sprite herosprite;
    Texture herotexture;
    Clock clock;
    Font font;
    
    std::vector <std::string > items;
    std::vector <std::string> quests;
public:
    
    void levelControl(std::vector<char**> &Levels , std::vector<Entity*> &ALL ,
                      RenderWindow& window);
    
    Player(float XF, float YF );
    
    Player();
        
    
    
    void load();
    
    void setLevel(int lvl){ this->level = lvl; }
    
    void savePlayer(std::string);
    void create(float,float);
    void turn(float,float);
    void add(std::string exp){
        this->items.push_back(exp);
    }
    void GUI(RenderWindow & window , std::vector <Entity*> ALL );
    
    int getHp() const {return this->hp;}
    
    int getType() const { return this->type;  }
    void setType(int exp) { this->type = exp; }
    
    void setHp(int exp) { this->hp = exp;}
    
    float getX() const { return this->x;}
    float getY() const { return this->y;}
    
    void displayInt(RenderWindow &  window , int  exp, float x ,float y){
        std::stringstream ss;
        ss << exp;
        std::string s = ss.str();
        Text hp("", font , 30);
        hp.setString(s);
        
        hp.setPosition(x, y);
        window.draw(hp); 
    }
    
    int getLevel() const { return this->level; }
    
    
    
    void setSpd(float exp){ this->speed = exp;}
    void setDr(int dir) { this->dr = dir; }
    
    void setX(float exp) { this->x = exp;}
    void setY(float exp) { this->y = exp;}
    
    void openInventory(RenderWindow & window , int selected );
    
    Sprite getSprite(){
        return this->herosprite;
    }
    
    void makeNewLevel(std::vector<char**> levels){
        this->x = 50;
        this->y = 50;
        this->level++;
        levels.push_back(makeLevel());
        this->herosprite.setPosition(x, y);
    }
    void PrintSome(RenderWindow &  window , std::string toPrint, float x ,float y , Color color);
    
    template <typename T>
    void eraseVect(std::vector<T> &vcs , int nmb) {
        vcs.erase(vcs.begin() + nmb);
    }
    
    FloatRect getRect(){
        return FloatRect(x , y , w ,h);
    }
    
    char** makeLevel();
    
    void useItem(int nmb){
        
        if(items[nmb] == "Book"){
            
        }
        if(items[nmb] == "Heal"){
            eraseVect(items , nmb);
            hp += 50;
            if(hp > 100){
                hp = 100;
            }
        }
        if(items[nmb] == "Sword"){
            this->attack += 20;
        }
    }
    
    
    void interactionWithMap(std::vector<char**> levels , std::vector <Entity*> ALL);
    
    int findSome( std::vector <Entity*> ALL , RenderWindow & window , int & nmb);
    
    void update(float time);
    
    void inventory(RenderWindow & window);
    
};
