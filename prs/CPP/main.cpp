#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Enemy.hpp"
#include "Heal.hpp"
#include "Player.hpp"
#include "SRTCT.hpp"

#include "Menu.hpp"

using namespace sf;

std::string Items[10];


//easy erase
template <typename T>
void eraseVect(std::vector<T> & vcs , int nmb) {
    vcs.erase(vcs.begin() + nmb);
}

//SFML print interfaced function
void PrintSome(RenderWindow &  window , std::string toPrint, float x ,float y , Color color , int fontSize , Font font){
    Text hp("", font , fontSize);
    hp.setString(toPrint);
    hp.setFillColor(color);
    hp.setPosition(x, y);
    window.draw(hp);
}

//return map of level
//to do
//generation of event
char** makeLevel(std::vector<Entity*> &ALL){
    char ** arr = new char *[25];
    for(int i = 0 ; i < 25 ; i++){
        arr[i] = new char[40];
    }
    for(int i = 0 ; i < 25 ; i++){
        for(int j = 0 ; j < 40 ; j++){
            if(i == 0 || j == 0 || j == 39 || i ==24){
                arr[i][j] = '0';
            }
            else{
                arr[i][j] = ' ';
            }
        }
    }
    return arr;
}

//render map , player , All Entities
void render(Sprite map , RenderWindow & window ,  std::vector<char**>levels ,   int lev , std::vector<Entity *>ALL , Player plr ){
    for (int i = 0; i < 25; i++) {
        for(int j = 0 ; j < 40 ; j++){
            if (levels[lev][i][j] == ' ') {
                map.setTextureRect(IntRect(0 , 0 ,16, 16));
            }
            if (levels[lev][i][j] == '0') {
                map.setTextureRect(IntRect(32 , 0 ,16, 16));
            }
            map.setPosition( 40 + j *16,40 + i*16);
            window.draw(map);
        }
    }
    for(auto  i = 0 ; i < ALL.size() ; i++){
        if(plr.getLevel() == ALL[i]->getLevel()){
            window.draw(ALL[i]->getSpr());
        }
    }       
    window.draw(plr.getSprite());
}

//render Fight map
void FightRender(char fight[10][40] , Sprite map , Player plr , RenderWindow & window , Entity * ent ) {
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 40; j++) {
            if (fight[i][j] == ' ') {
                map.setTextureRect(IntRect(0, 0, 16, 16));
            }
            if (fight[i][j] == '0') {
                map.setTextureRect(IntRect(32, 0, 16, 16));
            }
            map.setPosition(40 + j * 16, 40 +i * 16);
            window.draw(map);
        }
    }
    plr.displayInt(window, ent->getHp(), 100, 400);
    window.draw(plr.getSprite());
    window.draw(ent->getSpr());
}


//FIGHT FUNCTIONS//
void FIGHT(Player & plr, Entity * ent ) {
    if (plr.getType() == 0) {
        plr.setType(1);
    }
    plr.setX(140);
    plr.setY(90);
    ent->setSprPos(290, 90);
    
}
void attack(Player &plr , Entity * ent) {
    
    ent->setHp(ent->getHp() - 20);
    
    if ((rand() % 2) == 0) {
        
        plr.setHp(plr.getHp()- 20);
    }
}

void def(Player &plr, Entity * ent) {
    
}

void ult(Player &plr, Entity * ent) {
        ent->setHp(ent->getHp() - 80);
}

//make fight field
void makeFF(char fight[10][40]){
    for (int i = 0; i < 10; i++) {
        for(int j = 0 ; j < 40 ; j++){
            if(i == 0 || i == 9 || j == 0 || j == 39 ){
                fight[i][j] = '0';
            }else{
                fight[i][j] = ' ';
            }
        }
    }
}

//TODO BULLET CLASS
class Bullet : public Entity{
  
    Bullet(){
        
    }
    
    
    void move(){
        
    }
    
    
    ~Bullet(){
        
    }//end of destructor
    
};

//TODO TRADER
class Trader : public Entity{
    std::vector<std::string> toSell;
    std::vector<std::string> quests;
    
    
    
    Trader(float X , float Y , int lvl){
        
        for(int i = 0 ; i < 7 ; i++){
            toSell.push_back(Items[i]);
        }
        
    }
    
    
    ~Trader(){
        
    }
};

int main(int, char const**)
{
    Items[0] = "Bad Sword";
    Items[1] = "Mid Sword";
    Items[2] = "Perfect sword";
    Items[3] = "Bad Armor";
    Items[4] = "Mid Armor";
    Items[5] = "Perfect armor";
    Items[6] = "Heal";
    Items[7] = "Mana";
    
    char fight[10][40];
    makeFF(fight);
   
    std::vector<Entity*> ALL;
    std::vector<char**> levels;
    
    Player plr;
    
    Texture mapT;
    mapT.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/Sprites.png");
    Sprite map;
    map.setTexture(mapT);
    Font font;
    font.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/sansation.ttf");
    float tempX = 0;
    float tempY = 0;
    //float currentframe;
    
    int nmb;
 
    RenderWindow window(VideoMode(800, 600) , "GAME");
    
    Clock clock;
    Menu menu;
    menu.behavior(window ,plr, ALL ,levels);
  
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        Event event;
        
        vector<Entity*>::iterator it;
        //check if Entity died -> delete from vector
        for (it = ALL.begin(); it != ALL.end(); ) {
            if ((*it)->getDie() == true) {
                delete * it;
                it = ALL.erase(it);
            }
            else {
                ++it;
            }
        }
        //normal way
        if (plr.getType() == 0) {
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                plr.setDr(1);
                plr.setSpd(-0.1);
            }
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                plr.setDr(3);
                plr.setSpd(-0.1);
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                plr.setDr(0);
                plr.setSpd(0.1);
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                plr.setDr(2);
                plr.setSpd(0.1);
            }
            if (Keyboard::isKeyPressed(Keyboard::H)) {
                
                if (plr.findSome(ALL, window, nmb ) == 1) {
                    tempX = ALL[nmb]->getX() ;
                    tempY = ALL[nmb]->getY() ;
                    FIGHT(plr , ALL[nmb]);
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Tab)){
                menu.behavior(window, plr, ALL, levels);
            }
        }
        //fight way
        else if (plr.getType() == 1)  {
            
            if (plr.getHp() < 0) {
                return 0;
            }
            
            Entity * en = ALL[nmb];
            
            if (en->getHp() <= 0) {
                en->Die();
                plr.setType(0);
                if((rand() % 1) == 0){
                    plr.add(Items[6]);
                }else{
                   plr.add(Items[7]);
                }
            }
            Event keys;
            
            while (window.pollEvent(keys)) {
                if (keys.key.code == Keyboard::F && keys.type == Event::KeyReleased) {
                    attack(plr, en );
                }
                if (keys.key.code == Keyboard::V && keys.type == Event::KeyReleased) {
                    ult(plr, en );
                }
                if (keys.key.code == Keyboard::Escape && keys.type == Event::KeyReleased) {
                    plr.setType(0);
                    en->setSprPos(tempX, tempY);
                }
            }
        }
        plr.levelControl(levels, ALL , window);
        
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        
        plr.update(time);
        plr.inventory(window);
        plr.interactionWithMap(levels, ALL);
        window.clear();
    
        if(plr.getType() == 0 ){
            render(map, window, levels, plr.getLevel(), ALL , plr );
        }else if(plr.getType() == 1 ){
            FightRender(fight, map, plr, window , ALL[nmb]);
        }
        
        plr.GUI(window , ALL);
        
        window.display();
        
    }//end of gameloop
    //delete all dynamic allocated memory
    
    for(int i = 0 ; i < ALL.size() ; i++){
        delete ALL[i];
    }
    
    for(int i = 0 ; i < levels.size() ; i++){
        delete levels[i];
    }
    
    return 0;
}
