
#include "Screens.hpp"

Screens::Screens(float width, float height){
    if(!font.loadFromFile(resourcePath() + "zeroVelocity.ttf"))
        std::cout << "error";
    
    getReadyText.setFont(font);
    getReadyText.setPosition(700,850);
    getReadyText.setCharacterSize(75);
    getReadyText.setFillColor(Color::Yellow);
    getReadyText.setOutlineColor(Color::Blue);
    getReadyText.setOutlineThickness(3);
    getReadyText.setString("Get Ready");
    
    gameOverText.setFont(font);
    gameOverText.setPosition(700,850);
    gameOverText.setCharacterSize(75);
    gameOverText.setFillColor(Color::Yellow);
    gameOverText.setOutlineColor(Color::Blue);
    gameOverText.setOutlineThickness(3);
    gameOverText.setString("Game Over");
    
    youWonText.setFont(font);
    youWonText.setPosition(750,950);
    youWonText.setCharacterSize(75);
    youWonText.setFillColor(Color::Yellow);
    youWonText.setOutlineColor(Color::Blue);
    youWonText.setOutlineThickness(3);
    youWonText.setString("You Won");

    
}

void Screens::drawGetReadyText(RenderWindow& window){
        window.draw(getReadyText);
}

void Screens::drawGameOverScreen(RenderWindow& window){
    window.draw(gameOverText);

}
void Screens::resetClock(){
    clock.restart();
}

void Screens::drawYouWonText(RenderWindow& window){
    window.draw(youWonText);
}
