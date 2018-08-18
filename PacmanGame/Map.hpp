
#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <iostream>
#include <fstream>

using namespace sf;

const int tileSize = 65;

class Map{
private:
    RectangleShape *p1;
    RectangleShape *p2;
    RectangleShape *p3;
    
    Texture tileTexture;
    void readLevel(int);
    int numberOfTiles;
    RectangleShape titleImage;
    Texture titleImageTexture;
    String levelNumber = "Level1.txt";
    
public:
    Map(float, float);
    void drawLevel(RenderWindow&, int);
    int updateCurrentLevel(int&);
    RectangleShape* sendMap(int);
    void updateLevelNumber(String);
    String getLevelNumber();
};


#endif /* Map_hpp */
