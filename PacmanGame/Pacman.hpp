
#ifndef Pacman_hpp
#define Pacman_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Animation.hpp"
#include <iostream>
//#include "Map.hpp"

const int pacSize = 55;

enum lastKeyPressed{LEFT, RIGHT, UP, DOWN, NA};

class Pacman{
    
private:
    RectangleShape pac;
    RectangleShape mockPac;
    Texture pacTexture;
    Clock clock;    // clock to control speed of animation
    Clock clock2; // clock to control the speed of pac's movement
    Clock clock3;
    Clock clock4;
    Event gaming;
    RectangleShape *p; // a pointer to the map
    bool canMoveUp = true;
    bool canMoveDown = true;
    bool canMoveLeft = true;
    bool canMoveRight = true;
    lastKeyPressed currentDirection;
    
    float deltaTime;
    int pacCurrentOrientation; // where 0 is right, 1 is left, 2 is up and 3 is down

    lastKeyPressed last;     // and enum to check the last key pressed
    
    
    void controlPac(RenderWindow&); // control pac's movement
    void animatePac(Animation);
    void checkCollisionWithTiles();
    Vector2f lastUncollidedPosition;
    lastKeyPressed lastUncollidedDirection;
    void centerPac();
    bool isMoving();
    Vector2f currentPosition1;
    Vector2f currentPosition2;
    int currentTile;
    bool canMoveInDirection(lastKeyPressed);
    bool isNewPositionAMultiple(float, float);
    
public:
    Pacman(float, float);
    FloatRect getCurrentPosition();
    void drawPac(RenderWindow&, Animation&);
    Texture getPacTexture();
    void recieveMap(RectangleShape*);
    RectangleShape getPac();
    void resetPacPosition(float width, float height);
    void disableMovements();
    void makeTransparent();

    

};







#endif /* Pacman_hpp */
