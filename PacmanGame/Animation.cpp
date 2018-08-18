// animation is a class which takes a texture, a vector specifying the dimensions of the texture in terms of number of images, and a switchTime which is the time between different sprites
//the member function update takes the row and a time and cycles between the different sprites in that row for a specified texture


#include "Animation.hpp"

Animation::Animation(){
    totalTime = 0;
    currentImage.x = 0;
}

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime){
    
    this -> imageCount = imageCount; // this is needed because the constructor parameters and the private variables have
    this -> switchTime = switchTime; // the same name
    totalTime = 0;
    currentImage.x = 0;
    
    //    the height and width of each sprite
    textureRect.width = texture->getSize().x / imageCount.x;
    textureRect.height = texture->getSize().y / imageCount.y;
    
}
void Animation:: update(int row, float deltaTime){
    
    currentImage.y = row;
    totalTime+= deltaTime;
    
    if(totalTime >= switchTime){   // when enough time has passed, go to the next image
        totalTime -= switchTime;
        currentImage.x++;
        
        if(currentImage.x>= imageCount.x) // once last image is reached, go back to first image
            currentImage.x = 0;
    }
    
    textureRect.left = currentImage.x * textureRect.width; // reseting which sprite is displayed
    textureRect.top = currentImage.y * textureRect.height;
}

void Animation::setImageCountAndTextureRect(Vector2u imageCount1, IntRect textureRect1){
    imageCount = imageCount1;
    textureRect.width = textureRect1.width / imageCount1.x;
    textureRect.height = textureRect.height / imageCount1.y;
}
void Animation::setSwitchTime(float switchTime1){
    switchTime = switchTime1;
}
