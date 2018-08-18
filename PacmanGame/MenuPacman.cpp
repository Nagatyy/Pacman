#include "MenuPacman.hpp"
#include <iostream>


// constructor creates an unanimated version of the sprite
MenuPacman::MenuPacman(float width, float height){
    
    pac.setSize(Vector2f(125,125));
    pac.setPosition(width/3 - 50, height/3 + 225);
    if(!pacmanTexture.loadFromFile(resourcePath()+ "pac3.png")){
        std::cout << "error";
    }
    pac.setTexture(&pacmanTexture);
    deltaTime = 0;
}

// draws pacman with a call to animate to animate the sprite
void MenuPacman::drawPac(RenderWindow& window, Animation& animation){
    animatePac(animation);
    animation.update(0, deltaTime);
    window.draw(pac);
    
}
// a getter for the texture
Texture MenuPacman::getTexture(){
    return pacmanTexture;
}
// animating the pac
void MenuPacman::animatePac(Animation animation){
    deltaTime = clock.restart().asSeconds();
    pac.setTextureRect(animation.textureRect);
}
// move pacman  to next menu option
void MenuPacman::updatePosition(float width,float pos){
    pac.setPosition(width/3 - 75, pos-40);
}

