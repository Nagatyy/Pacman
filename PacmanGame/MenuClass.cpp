#include "MenuClass.hpp"
#include <iostream>

Menu::Menu(float width, float height){
    // menu constructor generates all parts of the Menu

    currentItem = 0;
    generateMain(width, height);
    generateSettings(width, height);
}
/*-----------------------------------------*/
void Menu::drawAll(RenderWindow& window){
    // check menu state and draw accordingly
    window.draw(titleImage);
   
    manageMenuState();
    
    if(currentState == MAINMENU)
        drawMainMenu(window);
    if(currentState == SETTINGS)
        drawSettingsMenu(window);
    if(currentState == HIGHSCORES)
        drawHighScoresMenu();
    if(closeTheWindow)
        window.close();
}
/*-----------------------------------------*/
// function to draw the MAIN Menu
void Menu::drawMainMenu(RenderWindow& window){
    for(int i = 0; i < numberOfItems; i ++)
        window.draw(menuOpts[i].text);

    window.draw(soundIcon);
    checkSelectedItem(window);
}
/*-----------------------------------------*/
// generate the elements of the main menu
void Menu::generateMain(float width, float height){
    if(!menuOpts[0].font.loadFromFile(resourcePath() + "zeroVelocity.ttf"))
        std::cout << "error";
    titleImage.setSize(Vector2f(1000,500));
    titleImage.setPosition(width/2-500, height/4 - 400);
    titleTexture.loadFromFile(resourcePath() + "titleImage.jpg");
    titleImage.setTexture(&titleTexture);
    
// the horizontal position of the text is a property of the screenwidth and the length of the text to give a centered look
    for(int i = 0; i < numberOfItems; i++){
        menuOpts[i].text.setFont(menuOpts[0].font);
        menuOpts[i].text.setString(mainItems[i]);
        menuOpts[i].text.setPosition(Vector2f(width/2 - mainItems[i].getSize()*15 - 100 , ((height-1000)/numberOfItems) * (i+1)+500));
    }
    
    if(!soundTexture.loadFromFile(resourcePath() + "soundOff.png"))
        std::cout<<"Error";
    soundIcon.setTexture(&soundTexture);
    soundIcon.setPosition(1500, 1500);
    soundIcon.setSize(Vector2f(100,100));
}
/*-----------------------------------------*/
// draw the settings menu
void Menu::drawSettingsMenu(RenderWindow& window){
    for(int i = 0; i < sNumberOfItems; i ++)
        window.draw(settingsOpts[i].text);
    window.draw(settingsTitle);
    window.draw(wasdKeys);
    window.draw(arrowKeys);
    
    checkSelectedItem(window);
    
}
/*-----------------------------------------*/
//generate the elements of the settings menu
void Menu::generateSettings(float width, float height){
    
    settingsTitle.setString("OPTIONS");
    settingsTitle.setFont(menuOpts[0].font);
    settingsTitle.setCharacterSize(75);
    settingsTitle.setFillColor(Color::Yellow);
    settingsTitle.setPosition(width/2 - 325,(height-1000)/numberOfItems + 350);
    
    for(int i = 0; i < sNumberOfItems; i++){
        settingsOpts[i].text.setFont(menuOpts[0].font);
        settingsOpts[i].text.setString(settingsItems[i]);
        if(settingsItems[i] == "BACK")
            settingsOpts[i].text.setPosition(Vector2f(width/2 - settingsItems[i].getSize()*15 - 100, ((height-1000)/sNumberOfItems) * (i+1)+800));
        else
            settingsOpts[i].text.setPosition(Vector2f(width/2 - settingsItems[i].getSize()*15 - 100, ((height-1000)/sNumberOfItems) * (i+1)+600));
    }
    
    if(!wasdTexture.loadFromFile(resourcePath() + "wasd.png"))
        std::cout<<"Error";
    if(!arrowTexture.loadFromFile(resourcePath() + "arrows.png"))
        std::cout << "Error";
    
    wasdKeys.setTexture(&wasdTexture);
    arrowKeys.setTexture(&arrowTexture);
    wasdKeys.setSize(Vector2f(150,150));
    arrowKeys.setSize(Vector2f(150,150));
    arrowKeys.setPosition(1500, settingsOpts[0].text.getPosition().y-75);
    wasdKeys.setPosition(1700, settingsOpts[0].text.getPosition().y-75);
    
    arrowKeys.setFillColor(Color::Yellow);
    
    wasdKeys.setFillColor(Color::White);
    
}
/*-----------------------------------------*/
// check which item is currently selected and update it accordingly
void Menu::checkSelectedItem(RenderWindow& window){
   
    updateFlag();

    if(Keyboard::isKeyPressed(Keyboard::Up) && keyPressFlag){
        keyPressFlag = false;
        currentItem--;
        manageCurrentItem();
    }
    if(Keyboard::isKeyPressed(Keyboard::Down) && keyPressFlag){
        keyPressFlag = false;
        currentItem++;
        manageCurrentItem();
    }
    
    if(currentState == MAINMENU){
        menuOpts[currentItem].text.setFillColor(Color::Yellow);
        menuOpts[currentItem].text.setCharacterSize(75);
        menuOpts[currentItem].text.setOutlineColor(Color::Blue);
        menuOpts[currentItem].text.setOutlineThickness(3);
    }
    if(currentState == SETTINGS){
        settingsOpts[currentItem].text.setFillColor(Color::Yellow);
        settingsOpts[currentItem].text.setCharacterSize(75);
        settingsOpts[currentItem].text.setOutlineColor(Color::Blue);
        settingsOpts[currentItem].text.setOutlineThickness(3);
    }

    if(currentState == MAINMENU){
        for(int i = 0; i < numberOfItems; i++)
            if(i != currentItem){
                menuOpts[i].text.setFillColor(Color::White);
                menuOpts[i].text.setCharacterSize(55);
                menuOpts[i].text.setOutlineColor(Color::Black);
            }
    }
    if(currentState == SETTINGS){
        for(int i = 0; i < sNumberOfItems; i++)
            if(i != currentItem){
                settingsOpts[i].text.setFillColor(Color::White);
                settingsOpts[i].text.setCharacterSize(55);
                settingsOpts[i].text.setOutlineColor(Color::Black);
            }
    }
}
/*-----------------------------------------*/
// flag to ensure 0.5s intervals between input in Menu
void Menu::updateFlag(){
    if(clock.getElapsedTime().asMilliseconds()>=500){
        clock.restart();
        keyPressFlag = true;
    }
}
/*-----------------------------------------*/
// manage the current item in the menu
void Menu::manageCurrentItem(){
    
    if(currentState == MAINMENU) {
        if(currentItem  > numberOfItems-1)
            currentItem = 0;
        if(currentItem < 0)
            currentItem = numberOfItems - 1;
    }
    else if(currentState == SETTINGS){
        if(currentItem  > sNumberOfItems-1)
            currentItem = 0;
        if(currentItem < 0)
            currentItem = sNumberOfItems - 1;
    }
}
/*-----------------------------------------*/
// get the position of the current item to place pac accordingly
float Menu::getCurrentItemPosition(int current){
    
    if(currentState == MAINMENU)
        return menuOpts[currentItem + current].text.getPosition().y;
    else if (currentState == SETTINGS)
        return settingsOpts[currentItem + current].text.getPosition().y;
}
/*-----------------------------------------*/
// update the current state of the Menu
void Menu::manageMenuState(){
    updateFlag();
    
    if(Keyboard::isKeyPressed(Keyboard::Return) && keyPressFlag && currentItem == 1 && currentState == MAINMENU){
        keyPressFlag = false;
        currentState = SETTINGS;
        currentItem = 0;
    }
    if(currentState == SETTINGS && keyPressFlag && currentItem == sNumberOfItems-1 && Keyboard::isKeyPressed(Keyboard:: Return)){
        currentItem = 0;
        keyPressFlag = false;
        currentState = MAINMENU;
    }
    // if the user presses exit on the MAINMENU, close the window
    if(currentState == MAINMENU && keyPressFlag && currentItem == numberOfItems-1 && Keyboard::isKeyPressed(Keyboard::Return))
        closeTheWindow = true;
    //if the user presses ESC while on the MAINMENU, close the widnow
    if(currentState == MAINMENU && keyPressFlag && Keyboard::isKeyPressed(Keyboard::Escape))
        closeTheWindow = true;
    

    // manage which controls are selected in settings
    if(currentState == SETTINGS && keyPressFlag && currentItem == 0 && Keyboard::isKeyPressed(Keyboard:: Return)){
        keyPressFlag = false;
        if(arrowKeys.getFillColor() == Color::Yellow){
            wasdKeys.setFillColor(Color::Yellow);
            arrowKeys.setFillColor(Color::White);
        }
        else{
            wasdKeys.setFillColor(Color::White);
            arrowKeys.setFillColor(Color::Yellow);
        }
    }
    
}
/*-----------------------------------------*/
// if true then the user chose to play with WASD
bool Menu::playWithWASD(){
    return wasdKeys.getFillColor() == Color::Yellow;
}
/*-----------------------------------------*/
bool Menu::startPlaying(){
    return (currentItem == 0 && currentState == MAINMENU && keyPressFlag &&  Keyboard::isKeyPressed(Keyboard::Return));
}
/*-----------------------------------------*/
void Menu::generateHighScores(){
    
    
    
}
void Menu::drawHighScoresMenu(){
    
}
