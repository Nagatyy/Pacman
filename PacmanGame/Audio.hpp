#ifndef Audio_hpp
#define Audio_hpp

#include <stdio.h>

#include <SFML/Audio.hpp>
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"


using namespace sf;
class Audio{
    
    
private:
    Sound volume;
    SoundBuffer buffer;
    
public:
    Audio(String a);
    void opening();
    void ghost();
    void bigcoin();
    void smallcoin();
    void close();
};



#endif /* Audio_hpp */
