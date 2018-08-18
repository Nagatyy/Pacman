#ifndef Screens_hpp
#define Screens_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Animation.hpp"
#include <iostream>
#include <string>

class Screens{


private:
    Text getReadyText;
    Text gameOverText;
    Text youWonText;
    Font font;
    Clock clock;
    
    
    
    
public:
    Screens(float, float);
    void drawGetReadyText(RenderWindow&);
    void drawGameOverScreen(RenderWindow&);
    void resetClock();
    void drawYouWonText(RenderWindow&);
    
    
    
};

#endif /* Screens_hpp */
