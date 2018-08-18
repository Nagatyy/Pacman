#ifndef Pickups_hpp
#define Pickups_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Animation.hpp"
#include <iostream>
#include "Map.hpp"

const int smallSize = 25;
const int bigSize = 65;

enum pickupType {smallDot, bigDot, life, speed};

struct pickup{
    RectangleShape sprite;
    pickupType type;
    bool visibility = true;
};


class Pickups{
private:
    pickup *p;          // pointer to the pickups
    RectangleShape* m;  // pointer to the map
    int numberOfPickups;
    int numberOfSmallDotsEaten = 0;
    int numberOfLives;
    float deltaTime;
    Clock clock;
    Clock immunityClock;
    Texture smallDotsTexture;
    Texture bigDotsTexture;
    Texture lifeTexture;
    
    void animatePickups(Animation);
    void updateVisibility(RectangleShape);
    bool immunity;
    void updateImmunity();

    
public:
    Pickups();
    void drawAll(RenderWindow&, Animation&, RectangleShape);
    void recieveMap(RectangleShape*);
    void populateMap();
    int updateNumberEaten();
    int getNumberOfPickups();
    bool isCurrentlyImmune();
    int getNumberOfLives();
    void increaseNumberOfLives();
    void decreaseNumberOfLives();
    void repopulateMap();

    
    Texture getTexture();
};




#endif /* Pickups_hpp */
