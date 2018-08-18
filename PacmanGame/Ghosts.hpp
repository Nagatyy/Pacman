// where do i delete the pointers?

#ifndef Ghosts_hpp
#define Ghosts_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Animation.hpp"
#include <iostream>
#include <time.h>

using namespace sf;

const int ghostSize = 55;



class Ghosts{
    
    enum direction {LEFT, RIGHT, UP, DOWN};  // left, right, up, down
    
private:
    
    RectangleShape *p;   // a pointer to the ghosts
    RectangleShape *m;
    RectangleShape pac;
    int numberOfGhosts;
    int row;
    Texture texture;
    
    float deltaTime;
    
    Clock clock;
    Clock clock2;
    
    direction currentDirection;
    
    
    bool canMoveUp = true;
    bool canMoveDown = true;
    bool canMoveLeft = true;
    bool canMoveRight = true;
    
    void deleteLastGhost();
    void manageRow();
    void setTextures();
    void manageGhosts();
    void initializeGhostPositions();
    bool checkCollisionWithTiles(int num);
    
    
public:
    Ghosts();
    void drawGhosts(RenderWindow&, Animation&);
    void animateGhost(Animation);
    Texture getTexture();
    void recieveMap(RectangleShape*);
    bool intersectWithPac(RectangleShape);
    void recolourGhosts(bool);
    void resetGhostPosition(RectangleShape);
    void resetAllGhosts();

    
    
};




#endif /* Ghosts_hpp */
