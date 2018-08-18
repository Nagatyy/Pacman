#ifndef Score_hpp
#define Score_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Animation.hpp"
#include <iostream>
#include <string>


class Score{
private:
    int currentScore;
    int numberEaten();
    int numberOfLives;
    Text displayedText;
    Text headingText;
    Font scoreFont;
    String displayedTextString;
    Texture lifeTexture;
    RectangleShape life[10];
    
    Clock timerClock;
    
    Text timerMinutes;
    Text timerSeconds;
    std::string minutesString;
    std::string secondsString;

    
public:
    Score(float, float);
    void recieveNumberEaten(int);
    void drawScore(RenderWindow&, int);
    void updateCurrentScore();
    void recieveNumberOfLives(int);
    void setNumberOfLives(int);
    
    void generateTimer(int);
    void drawTimer();
    void restartTimer();
    

};

#endif /* Score_hpp */
