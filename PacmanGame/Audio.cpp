#include "Audio.hpp"



Audio::Audio(String a) // Start sound
{
    buffer.loadFromFile(a);
    volume.setBuffer(buffer);
    volume.play();
    
}


//void Audio::ghost(String g) //ghost sound
//{
//    buffer.loadFromFile(g);
//    volume.setBuffer(buffer);
//    volume.play();
//}
//void Audio::bigcoin(String b) //big coin sound
//{
//    buffer.loadFromFile(b);
//    volume.setBuffer(buffer);
//    volume.play();
//}
//void Audio::smallcoin(String s) //small coin sound
//{
//    buffer.loadFromFile(s);
//    volume.setBuffer(buffer);
//    volume.play();
//}
//void Audio::close(String c) //end game sound
//{
//    buffer.loadFromFile(c);
//    volume.setBuffer(buffer);
//    volume.play();
//}
