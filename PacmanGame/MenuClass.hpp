/*- This class creates the Main Menu, with all of its varying functionality and uses.
 Additionals features can e added simply by adding elements to the mainItems and settingsItems arrays. The const ints numberOfItems and sNumberOfItems will also have to be adjusted. -*/
 

#ifndef MenuClass_hpp
#define MenuClass_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <string>
#include "MenuPacman.hpp"
#include <fstream>


const int numberOfItems = 4;
const int sNumberOfItems = 4;
enum MenuStates {MAINMENU, SETTINGS, HIGHSCORES};    // to keep track of the current state of the Menu

using namespace sf;

struct MenuOptions{
    Font font;
    Text text;
    String str;
};

class Menu{
private:
    MenuOptions menuOpts[numberOfItems];
    MenuOptions settingsOpts[sNumberOfItems];
    MenuStates currentState = MAINMENU;
    
    int currentItem;
    String mainItems[numberOfItems] = {"PLAY","OPTIONS", "High Scores", "EXIT"};
    String settingsItems[sNumberOfItems] = {"Controls:", "Reset Scores", "Sound", "BACK"};
    RectangleShape titleImage;
    RectangleShape arrowKeys;
    RectangleShape wasdKeys;
    RectangleShape soundIcon;   /////
    Text settingsTitle;
    Text highScoresText;
    Texture titleTexture;
    Texture arrowTexture;
    Texture wasdTexture;
    Texture soundTexture;    ////////
    Event event;
    bool keyPressFlag = false; // flag introduced because isKeyPressed would detect multiple key presses at once
    bool closeTheWindow = false;
    Clock clock;
    Clock clock2;

    void generateMain(float, float);
    void manageCurrentItem();
    void drawSettingsMenu(RenderWindow&);
    void generateSettings(float, float);
    void manageMenuState();
    void drawMainMenu(RenderWindow&);
    void generateHighScores();
    void drawHighScoresMenu();
    void updateFlag();
    void checkSelectedItem(RenderWindow&);
    
    
    
    

public:
    Menu(float, float);
    void drawAll(RenderWindow& window);
    float getCurrentItemPosition(int);
    bool playWithWASD();
    bool startPlaying();
    
};

#endif /* menuClass_hpp */
