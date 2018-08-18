#include "Pacman.hpp"


Pacman::Pacman(float width, float height){
    pac.setSize(Vector2f(pacSize,pacSize));
    pac.setPosition((width+pacSize)/2-30, (height+pacSize)/2+115);
    lastUncollidedPosition = Vector2f(width/2, height/2);
    if(!pacTexture.loadFromFile(resourcePath() + "ninjaPacman.png")){
        std::cout << "ninja pac texture not loaded";
    }
    pac.setTexture(&pacTexture);
    pacCurrentOrientation = 0;
    //last = NA;    // by default, he will move to the right first
    currentDirection = RIGHT;
    p = new RectangleShape[400];
}
//draw animated Pacman
void Pacman::drawPac(RenderWindow& window, Animation& animation){
    animatePac(animation);
    animation.update(pacCurrentOrientation, deltaTime);
    controlPac(window);
    window.draw(pac);
}
// animate Pacman
void Pacman::animatePac(Animation animation){
    deltaTime = clock.restart().asSeconds();
    pac.setTextureRect(animation.textureRect);
    
}
Texture Pacman::getPacTexture(){
    return pacTexture;
}
void Pacman::recieveMap(RectangleShape *recieved){
        p = recieved;
}

 //control direction of Pacmans movement
void Pacman::controlPac(RenderWindow& game){
    
    checkCollisionWithTiles();
    
    
    while (game.pollEvent(gaming))
			 {
                 switch (gaming.type)
                 {
                     case Event::Closed:
                         game.close();
                         break;
                     case Event::KeyPressed:
                         switch (gaming.key.code)
                     {
                         case Keyboard::Down:
                             last = DOWN;
                             if(canMoveDown && canMoveInDirection(DOWN)){
                                 pacCurrentOrientation = 3;
                                 canMoveDown = true;
                                 canMoveUp = true;
                                 canMoveRight = true;
                                 canMoveLeft = true;
                                 currentDirection = DOWN;
                                // pac.move(0,75);
                             }
                             break;
                         case Keyboard::Up:
                             last = UP;
                             if(canMoveUp && canMoveInDirection(UP)){
                                 pacCurrentOrientation = 2;
                                 canMoveDown = true;
                                 canMoveUp = true;
                                 canMoveRight = true;
                                 canMoveLeft = true;
                                 currentDirection = UP;
                               //  pac.move(0,-75);
                             }
                             break;

                         case Keyboard::Right:
                             last = RIGHT;
                             if(canMoveRight && canMoveInDirection(RIGHT)){
                                 pacCurrentOrientation = 0;
                                 canMoveDown = true;
                                 canMoveUp = true;
                                 canMoveRight = true;
                                 canMoveLeft = true;
                                 currentDirection = RIGHT;
                                // pac.move(75,0);
                             }
                             break;
                         case Keyboard::Left:
                             last = LEFT;
                             if (canMoveLeft && canMoveInDirection(LEFT)){
                                 pacCurrentOrientation = 1;
                                 canMoveDown = true;
                                 canMoveUp = true;
                                 canMoveRight = true;
                                 canMoveLeft = true;
                                 currentDirection = LEFT;
                                 //pac.move(-75,0);
                             }
                             break;

                         default:
                             pac.move(0,0);
                     }
                 }
             }

//     for continuout movement in the direction of the last key pressed
    
    switch (currentDirection) {  // in order for pac to continye moving, 25ms have to have passed (his speed)
        case LEFT:
            if(clock2.getElapsedTime().asMilliseconds() > 420 && canMoveLeft && currentDirection == LEFT && canMoveInDirection(LEFT)){
                pac.move(-(pacSize+10), 0);
                clock2.restart();
            }
            break;
        case RIGHT:
            if(clock2.getElapsedTime().asMilliseconds() > 420 && canMoveRight && currentDirection == RIGHT&& canMoveInDirection(RIGHT)){
                pac.move(pacSize+10, 0);
                clock2.restart();
            }
            break;
        case UP:
            if(clock2.getElapsedTime().asMilliseconds() > 420 && canMoveUp && currentDirection == UP&& canMoveInDirection(UP)){
                pac.move(0, -(pacSize+10));
                clock2.restart();
            }
            break;
        case DOWN:
            if(clock2.getElapsedTime().asMilliseconds() > 420 && canMoveDown && currentDirection == DOWN && canMoveInDirection(DOWN)){
                pac.move(0, pacSize+10);
                clock2.restart();
            }
            break;
    }
    
    
    
    
}

void Pacman::checkCollisionWithTiles(){
    currentTile = 0;
    for(int i = 0; i < 400; i++)
        if(pac.getGlobalBounds().intersects((*(p+i)).getGlobalBounds())){
            currentTile = i;
            if((*(p+i)).getTexture() != NULL){   // if pac intersects with an element that has a texture(tile)
                if(pacCurrentOrientation == 2){
                    canMoveUp = false;
                    pac.setPosition(pac.getPosition().x, pac.getPosition().y+1);
                }
                else if(pacCurrentOrientation == 3){
                    canMoveDown = false;
                    pac.setPosition(pac.getPosition().x, pac.getPosition().y-1);
                }
                else if(pacCurrentOrientation == 0){
                    canMoveRight = false;
                    pac.setPosition(pac.getPosition().x-1, pac.getPosition().y);
                }
                else if(pacCurrentOrientation == 1){
                    canMoveLeft = false;
                    pac.setPosition(pac.getPosition().x+1, pac.getPosition().y);
                }
            }
        }
}

bool Pacman::canMoveInDirection(lastKeyPressed direction){
    RectangleShape mockPac;
    mockPac.setPosition(pac.getPosition());
    mockPac.setSize(Vector2f(pacSize,pacSize));
    
        if(direction == LEFT){
            mockPac.move(-15,0);
            if(mockPac.getGlobalBounds().intersects((*(p+currentTile-1)).getGlobalBounds()))
                if((*(p+currentTile-1)).getTexture() != NULL)
                    return false;
        }
        if(direction == RIGHT){
            mockPac.move(15,0);
            if(mockPac.getGlobalBounds().intersects((*(p+currentTile+1)).getGlobalBounds()))
                if((*(p+currentTile+1)).getTexture() != NULL)
                    return false;
        }
        if(direction == UP){
            mockPac.move(0,-15);
            if(mockPac.getGlobalBounds().intersects((*(p+currentTile-20)).getGlobalBounds()))
                if((*(p+currentTile-20)).getTexture() != NULL)
                    return false;
        }
        if(direction == DOWN){
            mockPac.move(0,15);
            if(mockPac.getGlobalBounds().intersects((*(p+currentTile+20)).getGlobalBounds()))
                if((*(p+currentTile+20)).getTexture() != NULL)
                    return false;
        }
    
    return true;

}
RectangleShape Pacman::getPac(){
    return pac;
}
void Pacman::resetPacPosition(float width, float height){
    pac.setPosition((width+pacSize)/2-30, (height+pacSize)/2+117.5);
    pacCurrentOrientation = 0;
    currentDirection = NA;

}
void Pacman::disableMovements(){
    pacCurrentOrientation = 0;
    currentDirection = NA;
}
void Pacman::makeTransparent(){
    pac.setFillColor(Color::Transparent);
}
