#include "Pickups.hpp"

Pickups::Pickups(){
    m = new RectangleShape[400];
    p = new pickup[400];
    immunity = false;
    numberOfLives = 3;

    if(!smallDotsTexture.loadFromFile(resourcePath() + "smallDots.png"))
        std::cout << "Dots Texture not loaded";
    if(!lifeTexture.loadFromFile(resourcePath() + "life.png"))
        std::cout << "Life Texture not loaded";

}
/*--------recieve map to initialize positions of pickups------------*/
void Pickups::recieveMap(RectangleShape* recieved){
    m = recieved;
}
/*--------------populating the map w/ pickups---------------*/
void Pickups::populateMap(){
    numberOfPickups = 0;
    for(int i = 0; i < 400; i++)
        if((*(m+i)).getTexture() == NULL){   // if it is a path
            numberOfPickups++;
        }
    
    int j = 0;
    for(int i = 0; i < 400; i++)
        if((*(m+i)).getTexture() == NULL){   // if it is a path
            if(i == 21 || i == 38 || i == 115 || i == 304 ||i == 361 || i == 378){
                (p+j)->type = bigDot;
                (p+j)->sprite.setPosition((*(m+i)).getPosition().x, (*(m+i)).getPosition().y);
                (p+j)->sprite.setSize(Vector2f(bigSize,bigSize));
                (p+j)->sprite.setTexture(&smallDotsTexture);
                (p+j)->sprite.setFillColor(Color::Yellow);
            }
            else if(i == 268){
                (p+j)->type = life;
                (p+j)->sprite.setPosition((*(m+i)).getPosition().x, (*(m+i)).getPosition().y);
                (p+j)->sprite.setSize(Vector2f(bigSize,bigSize));
                (p+j)->sprite.setTexture(&lifeTexture);

            }
            else{
                (p+j)->type = smallDot;
                (p+j)->sprite.setPosition((*(m+i)).getPosition().x+22, (*(m+i)).getPosition().y+22);
                (p+j)->sprite.setSize(Vector2f(smallSize,smallSize));
                (p+j)->sprite.setTexture(&smallDotsTexture);
            }
            j++;
        }
}
/*--------draw pickups with animation------------*/
void Pickups::drawAll(RenderWindow& window, Animation& animation, RectangleShape pac){
    populateMap();
    updateVisibility(pac);
    updateNumberEaten();
    updateImmunity();
    
    for(int i = 0; i < numberOfPickups; i++){
        if ((p+i) -> visibility){
                animatePickups(animation);
                animation.update(0, deltaTime);
                window.draw((p+i)->sprite);
            
        }
    }
}
/*--------Animate the pickups----------------------*/
void Pickups::animatePickups(Animation animation){
    deltaTime = clock.restart().asSeconds();
    for(int i = 0; i < numberOfPickups; i++){
        if((p+i)->type!= life)
            (*(p+i)).sprite.setTextureRect(animation.textureRect);
    }
}
/*--------return texture (needed for animation)----------------------*/
Texture Pickups::getTexture(){
    return smallDotsTexture;
}
/*----------Check if eaten-----------------*/
void Pickups::updateVisibility(RectangleShape pac){
    for(int i = 0; i < numberOfPickups; i++)
        if(pac.getGlobalBounds().intersects((p+i)->sprite.getGlobalBounds())){
            numberOfSmallDotsEaten++;
            if((p+i)->type == bigDot && (p+i)-> visibility){
                immunity = true;
                immunityClock.restart();
            }
            if((p+i)->type == life && (p+i)-> visibility)
                numberOfLives++;
            (p+i)-> visibility = false;
        }
}
/*---------Update number of eaten dots-------------*/
int Pickups::updateNumberEaten(){
    numberOfSmallDotsEaten = 0;
    for(int i = 0; i < numberOfPickups; i++){
        if(!(p+i)->visibility)
            numberOfSmallDotsEaten++;
    }
    return numberOfSmallDotsEaten;
}
int Pickups::getNumberOfPickups(){
    return numberOfPickups;
}
/*---------------------*/
void Pickups::updateImmunity(){
    if(immunityClock.getElapsedTime().asSeconds() >= 5){
        immunityClock.restart();
        immunity = false;
    }
}
/*---------------------*/
bool Pickups::isCurrentlyImmune(){
    return immunity;
}
int Pickups::getNumberOfLives(){
    return numberOfLives;
}
void Pickups::increaseNumberOfLives(){
    numberOfLives++;
}
void Pickups::decreaseNumberOfLives(){
    numberOfLives--;
}
void Pickups::repopulateMap(){
    for(int i = 0; i < numberOfPickups; i++)
        (p+i)-> visibility = true;

}


















