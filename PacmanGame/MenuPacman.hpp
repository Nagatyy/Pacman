
#ifndef MenuPacman_hpp
#define MenuPacman_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Animation.hpp"

using namespace sf;

class MenuPacman{
    
private:
    RectangleShape pac;
    Texture pacmanTexture;
    float deltaTime;
    Clock clock;

public:
    MenuPacman(float, float);
    void drawPac(RenderWindow&, Animation&);
    Texture getTexture();
    void animatePac(Animation);
    void updatePosition(float, float);

    
    
    
    
};

#endif /* MenuPacman_hpp */
