#include "Ghosts.hpp"


Ghosts::Ghosts(){
    numberOfGhosts = 4;
    p = new RectangleShape[numberOfGhosts];
    if(!texture.loadFromFile(resourcePath() + "ghostsSheet.png"))
        std::cout << "Ghost Texutre not loaded";
    
    for(int i = 0; i< numberOfGhosts; i++){
        (*(p+i)).setSize(Vector2f(ghostSize,ghostSize));
        (*(p+i)).setTexture(&texture);
        
        if(i == 0)
            (*(p+i)).setPosition(495.5, 296.5);
        else if(i == 1)
            (*(p+i)).setPosition(1479.5, 296.5);
        else if(i == 2)
            (*(p+i)).setPosition(504.5, 1401.5);
        else if(i == 3){
            (*(p+i)).setPosition(1479.5, 1401.5);
        }
        
        
    }
}


void Ghosts::drawGhosts(RenderWindow& window, Animation& animation){
     //draw all ghosts in animated form
    
    manageGhosts();
    
        for(int i = 0; i< numberOfGhosts; i++){
            animateGhost(animation);
            animation.update(i%4, deltaTime);
            window.draw(*(p+i));
        }
    
    
}

void Ghosts::recieveMap(RectangleShape* recieved ){
    m = recieved;
}

void Ghosts::animateGhost(Animation animation){
    deltaTime = clock.restart().asSeconds();
    for(int i = 0; i < numberOfGhosts; i++){
        (*(p+i)).setTextureRect(animation.textureRect);
    }
}

Texture Ghosts::getTexture(){
    return texture;
}


void Ghosts::manageGhosts(){
    
    if(clock2.getElapsedTime().asMilliseconds() > 600){
        clock2.restart();
        for(int i=0; i<4; i++){
            bool moved = false;
            while(!moved){
                int num = rand()%4;
                switch(num){
                    case 0:
                        currentDirection = RIGHT;
                        break;
                    case 1:
                        currentDirection = LEFT;
                        break;
                    case 2:
                        currentDirection = UP;
                        break;
                    case 3:
                        currentDirection = DOWN;
                        break;
                }
                if(currentDirection == RIGHT)
                    (*(p+i)).move(ghostSize+10, 0);
                else if (currentDirection == LEFT)
                    (*(p+i)).move(-(ghostSize+10), 0);
                else if (currentDirection == UP)
                    (*(p+i)).move(0, -(ghostSize+10));
                else if (currentDirection == DOWN)
                    (*(p+i)).move(0, ghostSize+10);
                
                moved =  checkCollisionWithTiles(i);
            }
        }
    }
}

bool Ghosts::checkCollisionWithTiles(int num)
{
    for(int i = 0; i < 400; i++){
        if((*(p+num)).getGlobalBounds().intersects((*(m+i)).getGlobalBounds()))
            if((*(m+i)).getTexture() != NULL){   // if pac intersects with an element that has a texture(tile)
                if(currentDirection == UP){
                    (*(p+num)).move(0, ghostSize+10);
                }
                else if(currentDirection == DOWN){
                    (*(p+num)).move(0, -(ghostSize+10));
                }
                else if(currentDirection == RIGHT){
                    (*(p+num)).move(-(ghostSize+10), 0);
                }
                else if(currentDirection == LEFT){
                    (*(p+num)).move(ghostSize+10, 0);
                }
                return false;
            }
    }
    return true;
}
bool Ghosts::intersectWithPac(RectangleShape pac){
    for(int i = 0; i < 4; i++){
        if((*(p+i)).getGlobalBounds().intersects(pac.getGlobalBounds()))
            return true;
    }
}
void Ghosts::recolourGhosts(bool immune){
    
    if(immune)
        for(int i = 0; i < numberOfGhosts; i++)
            (*(p+i)).setFillColor(Color::Magenta);
    else
        for(int i = 0; i < numberOfGhosts; i++)
            (*(p+i)).setFillColor(Color::White);
}

void Ghosts::resetGhostPosition(RectangleShape pac){
    for(int i = 0; i < 4; i++){
        if((*(p+i)).getGlobalBounds().intersects(pac.getGlobalBounds()))
            (*(p+i)).setPosition(959.5, 815.5);
            }
}
void Ghosts::resetAllGhosts(){
    for(int i = 0; i < numberOfGhosts; i++){
        if(i == 0)
            (*(p+i)).setPosition(495.5, 296.5);
        else if(i == 1)
            (*(p+i)).setPosition(1479.5, 296.5);
        else if(i == 2)
            (*(p+i)).setPosition(504.5, 1401.5);
        else if(i == 3)
            (*(p+i)).setPosition(1479.5, 1401.5);
}
}
























// spriteSheet: https://raw.githubusercontent.com/vilbeyli/Pacman/master/Assets/Sprites/spritesheet.png
