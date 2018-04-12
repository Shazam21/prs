#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#pragma once

#include "Enemy.hpp"
#include "Player.hpp"
#include "Heal.hpp"

#define LOG(x) std::cout << x << std::endl

class Menu{
    bool show;
    bool in_game;
    Font font;
    std::vector<std::string> ways;
    std::vector<std::string> files;
    std::string filepath;
public:
    
    Menu(){
        show = false;
        in_game = false;
        ways.emplace_back("Continue");//0
        ways.emplace_back("New game");//1
        ways.emplace_back("Load game");//2
        ways.emplace_back("Save game");//3
        ways.emplace_back("Exit game");//4
       
        font.loadFromFile("/Users/nikolajkostin/Desktop/prs/prs/Reources/sansation.ttf");
        filepath = "/Users/nikolajkostin/Desktop/prs/prs/CPP/File.txt";
        
    }
    
    void PrintSome(RenderWindow &  window , std::string toPrint, float x ,float y , Color color , int fontSize , Font font){
        Text hp("", font , fontSize);
        hp.setString(toPrint);
        hp.setFillColor(color);
        hp.setPosition(x, y);
        window.draw(hp);
    }
    
    void behavior(RenderWindow& window , Player &plr , std::vector<Entity*> &ALL , std::vector<char**> &levels ){
        show = true;
        int selected = 0;
        int way = 0;
        while(show && window.isOpen()){
            window.clear();
            Event event;
            PrintSome(window, "THE LEGEGND\nOF ZELDA", 300, 100, Color::White, 40, font);
            for(int i = 0 ; i < ways.size();i++){
                if(selected == i ){
                    PrintSome(window, ways[i], 300, 300 + (i * 40) , Color::Blue , 30 , font);
                }else{
                    PrintSome(window, ways[i], 300, 300 + (i * 40), Color::White, 30, font);
                    
                }
                
            }
            way = this->handleInput(selected , window);
            if(way == -1 ){
                window.close();
            }
            if(way == 1 ){
                if(selected == 1){
                    show = false;
                    this->start(plr, ALL, levels);
                }
                if(selected == 3){
                    this->save(plr , ALL , levels);
                }
                if(selected == 0){
                    this->load(plr , levels , ALL);
                    show = false;
                }
                if(selected == 4){
                    window.close();
                }
            }
            while(window.pollEvent(event)){
                if(event.type == Event::Closed){
                    window.close();
                }
            }
            
            window.display();
        }//end of menu loop
    }
    
    void start(Player & plr , std::vector<Entity*> &ALL , std::vector<char**> &levels){
        plr.create(60, 60);
        ALL.emplace_back(new Enter(220 ,100 , plr.getLevel()));
        ALL.emplace_back(new Enemy(200,200 , plr.getLevel()));
        levels.emplace_back(makeLevel());
        
    }
    
    char** makeLevel(){
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
    
    void load(Player & plr , std::vector <char**>& levels , std::vector<Entity*>ALL ){
        
        std::ifstream file(filepath );
        
        std::string s;
        std::vector<std::string> props;
        int type = -1 ;
        int counter = 0;
        int lev = -1 ;
        
        
        //Entity
        std::vector<std::string> entProps;
        while(getline(file , s) && !file.eof()){
          
            if(s.find("PLAYER") != std::string::npos){
                type = 1;
                continue;
            }
            if(s.find("level") != std::string::npos){
                lev++;
                levels.push_back(makeLevel());
                type = 0;
                counter = 0;
                continue;
            }
            if(s.find("Entity") != std::string::npos){
                type = 2;
                continue;
            }
            if(type == 0 ){
                if(counter < 25){
                    for(int i = 0 ; i < 40 ; i++){
                        levels[lev][counter][i] = s[i];
                    }
                    counter++;
                }else{
                    type = -1;
                }
            }
            if(type == 2 ){
                entProps.push_back(s);
            }
            if(type == 1){
                props.emplace_back(s);
            }
        }
        int ctd = 0;
        int cc = 0;
        while(cc < entProps.size()){
            float x = stof(entProps[cc]);
            float y = stof(entProps[cc + 1]);
            int hp = stoi(entProps[cc + 2]);
            int level = stoi(entProps[cc + 3]);
            int type = stoi(entProps[cc + 4]);
            
            
            if(type == 1){
                ALL.push_back(new Enemy(x , y , level));
                ALL[ctd]->setHp(hp);
            }
            if(type == 0){
                ALL.push_back(new Enter(x , y , level));
            }
            ctd++;
            cc += 5;
        }
        
        plr.create(stof(props[0]), stof(props[1]));
        plr.setLevel(stoi(props[2]));
        plr.setHp(stof(props[3]));
    }//end of loadFunc
    
    void save(Player & plr , std::vector<Entity*> ALL , std::vector<char**> levels){
        std::ofstream file(filepath);
        
        if(!file.is_open()){
            std::cout << "File cant be open" << std::endl;
        }
        
        for(int i = 0 ; i < levels.size();i++){
            file << "level" << ' ' << i << std::endl ;
            for(int j = 0 ; j < 25 ; j++){
                for(int c = 0 ; c < 40 ; c++){
                    file << levels[i][j][c] ;
                }
                file << std::endl;
                
            }
        }
        std::stringstream ss[10];
        
        ss[0] << plr.getX();
        ss[1] << plr.getY();
        ss[2] << plr.getLevel();
        ss[3] << plr.getHp();
        
        file << "PLAYER" << std::endl;
        file << ss[0].str() << std::endl;//x
        file << ss[1].str() << std::endl;//y
        file << ss[2].str() << std::endl;//level
        file << ss[3].str() << std::endl;//hp
        
        for(int i = 0 ; i < ALL.size();i++){
            std::stringstream sts[5];
            sts[0] << ALL[i]->getX();
            sts[1] << ALL[i]->getY();
            sts[2] << ALL[i]->getHp();
            sts[3] << ALL[i]->getLevel();
            sts[4] << ALL[i]->getType();
            sts[5] << ALL[i]->getDie();
            
            
            file << "Entity" << std::endl;
            file << sts[0].str() << std::endl;//x
            file << sts[1].str() << std::endl;//y
            file << sts[2].str() << std::endl;//hp
            file << sts[3].str() << std::endl;//level
            file << sts[4].str() << std::endl;//type
            
            
        }
        file.close();
    }//end save funt
    
    ~Menu(){
        
    }
    
    int handleInput(int &selected , RenderWindow & window){
        Event event;
        while(window.pollEvent(event)){
            if(event.key.code == Keyboard::W && selected > 0 && event.type == Event::KeyReleased){
                selected--;
            }
            if(event.key.code == Keyboard::S  && event.type == Event::KeyReleased&&
               selected < ways.size() -1){
                selected++;
            }
            if(event.key.code == Keyboard::E && event.type == Event::KeyReleased){
                return 1;
            }
        }
        return 0;
    }//end of handleInput
};
