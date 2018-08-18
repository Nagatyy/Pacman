#include "Score.hpp"


Score::Score(float width, float height){
    currentScore = 0;
    numberOfLives = 3;
    
    displayedText.setPosition(width/10-100, height/10);
    displayedText.setCharacterSize(75);
    displayedText.setFillColor(Color::Yellow);
    displayedText.setOutlineColor(Color::Blue);
    displayedText.setOutlineThickness(3);

    headingText.setPosition(width/10 - 200, height/10 - 100);
    headingText.setCharacterSize(75);
    headingText.setFillColor(Color::Yellow);
    headingText.setOutlineColor(Color::Blue);
    headingText.setOutlineThickness(3);
    headingText.setString("SCORE:");

    
    if(!scoreFont.loadFromFile(resourcePath() + "zeroVelocity.ttf"))
        std::cout << "Score Font not loaded";
    if(!lifeTexture.loadFromFile(resourcePath() + "life.png"))
        std::cout << "Life Texture not loaded";
    displayedText.setFont(scoreFont);
    headingText.setFont(scoreFont);
    
    displayedTextString = std::to_string(currentScore);
    displayedText.setString(displayedTextString);
    

    
    for(int i = 0; i < 10; i++){
        life[i].setTexture(&lifeTexture);
        life[i].setSize(Vector2f(150,150));
        life[i].setPosition(width-300,i*150);
    }
    
    timerMinutes.setFont(scoreFont);
    timerMinutes.setPosition(width/10-165, height/10+300);
    timerMinutes.setCharacterSize(40);
    timerMinutes.setFillColor(Color::Yellow);
    timerMinutes.setOutlineColor(Color::Blue);
    timerMinutes.setOutlineThickness(3);
    
    timerSeconds.setFont(scoreFont);
    timerSeconds.setPosition(width/10-100, height/10+300);
    timerSeconds.setCharacterSize(40);
    timerSeconds.setFillColor(Color::Yellow);
    timerSeconds.setOutlineColor(Color::Blue);
    timerSeconds.setOutlineThickness(3);
    
}

void Score::drawScore(RenderWindow& window, int level){
    updateCurrentScore();
    generateTimer(level);
    
    for(int i = 0; i < numberOfLives; i++){
        window.draw(life[i]);
    }
    
    window.draw(headingText);
    window.draw(displayedText);
    window.draw(timerMinutes);
    window.draw(timerSeconds);
}
void Score::recieveNumberEaten(int num){
    currentScore = 10*num;
}
void Score::updateCurrentScore(){
    displayedTextString = std::to_string(currentScore);
    displayedText.setString(displayedTextString);
}
void Score::setNumberOfLives(int n){
    numberOfLives = n;
}
void Score::generateTimer(int level){
    if(level == 1){
        int minutes = 5 - (timerClock.getElapsedTime().asSeconds()/60);
        minutesString = std::to_string(minutes);
        minutesString.append(":");
        timerMinutes.setString(minutesString);
        
        int seconds = 60 - int(timerClock.getElapsedTime().asSeconds())%60;
        secondsString = std::to_string(seconds);
        timerSeconds.setString(secondsString);
    }
    if(level == 2){
        int minutes = 4 - (timerClock.getElapsedTime().asSeconds()/60);
        minutesString = std::to_string(minutes);
        minutesString.append(":");
        timerMinutes.setString(minutesString);
        
        int seconds = 60 - int(timerClock.getElapsedTime().asSeconds())%60;
        secondsString = std::to_string(seconds);
        timerSeconds.setString(secondsString);
    }
    if(level == 3){
        int minutes = 3 - (timerClock.getElapsedTime().asSeconds()/60);
        minutesString = std::to_string(minutes);
        minutesString.append(":");
        timerMinutes.setString(minutesString);
        
        int seconds = 60 - int(timerClock.getElapsedTime().asSeconds())%60;
        secondsString = std::to_string(seconds);
        timerSeconds.setString(secondsString);
    }

}
void Score::restartTimer(){
    timerClock.restart();
}

