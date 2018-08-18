#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>


using namespace sf;

class Animation{
    
private:
    Vector2u imageCount, currentImage;      // to store the amount of images per row and current image
    float totalTime, switchTime;     // ST is time between images
    
  
public:
    Animation();
    Animation(Texture* texture, Vector2u imageCount, float switchTime);
    IntRect textureRect;
    void update(int row, float deltaTime);
    void setImageCountAndTextureRect(Vector2u, IntRect);
    void setSwitchTime(float );

    
    
};

#endif /* Animation_hpp */
