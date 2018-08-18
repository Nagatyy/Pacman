#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include "MenuClass.hpp"
#include "MenuPacman.hpp"
#include "Animation.hpp"
#include "Ghosts.hpp"
#include "Pacman.hpp"
#include "Map.hpp"
#include "Pickups.hpp"
#include <time.h>
#include "Score.hpp"
#include "Screens.hpp"

using namespace sf;

enum gameState {MENU, PLAYING, ENDSCREEN};
enum currentLevel {Level1, Level2, Level3, ENDGAME};

void handleEvent(RenderWindow&);

int main(){
    srand(time(NULL));
    Clock universal;
    
    RenderWindow window;
    window.create(VideoMode(2048,2048), "Pacman");

    gameState currentGameState = MENU;
    currentLevel level = Level1;
    
    
    Menu mainMenu(window.getSize().x, window.getSize().y);
    MenuPacman MenuPac(window.getSize().x, window.getSize().y);
    Ghosts ghosts;
    Pacman pac(window.getSize().x, window.getSize().y);
    Map map(window.getSize().x, window.getSize().y);
    Pickups pickups;
    Score score(window.getSize().x, window.getSize().y);
    Screens screens(window.getSize().x, window.getSize().y);
    
    Texture menuPacmanTexture = MenuPac.getTexture();
    Texture ghostsTexture = ghosts.getTexture();
    Texture pacmanTexture = pac.getPacTexture();
    Texture smallDotsTexture = pickups.getTexture();
    
    
    float pacCurrentPosition;
    bool flag = true;
    
    
    Animation animation(&menuPacmanTexture, Vector2u(4,1), 0.125);
    Animation animation2(&ghostsTexture, Vector2u(8,4), 0.2);
    Animation animation3(&pacmanTexture, Vector2u(6,4), 0.05);
    Animation animation4(&smallDotsTexture, Vector2u(3,1), 0.25);
    
    while(window.isOpen()){
        
        
        if(currentGameState == MENU){
            pacCurrentPosition = mainMenu.getCurrentItemPosition(0);
            MenuPac.updatePosition(window.getSize().x, pacCurrentPosition);
            handleEvent(window);
            mainMenu.drawAll(window);
            MenuPac.drawPac(window, animation);
            //once play is pressed, start playing
            if(mainMenu.startPlaying())
                currentGameState = PLAYING;
        }
        if(currentGameState == PLAYING){
            if(flag){
                universal.restart();
                flag = false;
            }

            if(level == Level1){
                map.drawLevel(window,1);
                ghosts.recieveMap(map.sendMap(1));
                pickups.recieveMap(map.sendMap(1));
                pac.recieveMap(map.sendMap(1));
                score.drawScore(window, 1);

                if(universal.getElapsedTime().asSeconds() < 4){
                    pac.disableMovements();
                    pac.resetPacPosition(window.getSize().x, window.getSize().y);
                    screens.drawGetReadyText(window);
                }
            
                if(pickups.updateNumberEaten() >=208){ // 208
                    level = Level2;
                    pac.resetPacPosition(window.getSize().x, window.getSize().y);
                    ghosts.resetAllGhosts();
                    pickups.recieveMap(map.sendMap(2));
                    pickups.repopulateMap();
                    screens.resetClock();
                    score.restartTimer();
                    flag = true;
                }
            }
            else if(level == Level2){
                universal.restart();
                map.drawLevel(window,2);
                ghosts.recieveMap(map.sendMap(2));
                pac.recieveMap(map.sendMap(2));
                pickups.recieveMap(map.sendMap(2));
                score.drawScore(window, 2);

                
                if(pickups.updateNumberEaten() >= 211){ // 211
                    level = Level3;
                    pac.resetPacPosition(window.getSize().x, window.getSize().y);
                    ghosts.resetAllGhosts();
                    pickups.recieveMap(map.sendMap(3));
                    pickups.repopulateMap();
                    screens.resetClock();
                    score.restartTimer();
                }
            }
            else if(level == Level3){
                map.drawLevel(window,3);
                ghosts.recieveMap(map.sendMap(3));
                pickups.recieveMap(map.sendMap(3));
                pac.recieveMap(map.sendMap(3));
                score.drawScore(window, 3);

                
                if(pickups.updateNumberEaten() >= 209){ // or 209
                    screens.drawGameOverScreen(window);
                    pac.disableMovements();
                    pac.resetPacPosition(window.getSize().x, window.getSize().y);
                    if(pickups.getNumberOfLives() >=0){
                        screens.drawYouWonText(window);
                        pac.makeTransparent();
                    }
                    
                }
            }
            
            ghosts.recolourGhosts(pickups.isCurrentlyImmune());
            if(ghosts.intersectWithPac(pac.getPac()))
                if(pickups.isCurrentlyImmune())
                    ghosts.resetGhostPosition(pac.getPac());
                else{
                    pac.resetPacPosition(window.getSize().x, window.getSize().y);
                    pickups.decreaseNumberOfLives();
                }
            
            score.setNumberOfLives(pickups.getNumberOfLives());
            score.recieveNumberEaten(pickups.updateNumberEaten());
            pickups.drawAll(window, animation4, pac.getPac());
            ghosts.drawGhosts(window, animation2);
            pac.drawPac(window, animation3);
            
            if(pickups.getNumberOfLives() < 0){
                pac.disableMovements();
                pac.resetPacPosition(window.getSize().x, window.getSize().y);
                screens.drawGameOverScreen(window);
            }

            handleEvent(window);
            
        }
        window.display();
        window.clear();
    }
   
}

void handleEvent(RenderWindow& window){
    
    Event event;
   
    while(window.pollEvent(event)){
        switch(event.type){
            case Event::Closed:
                window.close();
                std::cout << "closed";
                break;
        }
    }
}

