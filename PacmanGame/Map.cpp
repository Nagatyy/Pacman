#include "Map.hpp"

Map::Map(float width, float height){
    numberOfTiles = 400;
    p1 = new RectangleShape[numberOfTiles];
    p2 = new RectangleShape[numberOfTiles];
    p3 = new RectangleShape[numberOfTiles];

    if(!tileTexture.loadFromFile(resourcePath() + "tileTexture2.png"))
        std::cout << "Tile Texture not loaded";
    if(!titleImageTexture.loadFromFile(resourcePath() + "titleImage.jpg"))
        std::cout << "Title image texture not loaded";
    // initialize positions of map tiles
    int j = 0;
    for(int i = 0; i < numberOfTiles; i ++){
        (*(p1+i)).setSize(Vector2f(tileSize,tileSize));
        if(i%20==0)
            (*(p1+i)).setPosition((i%20)*tileSize+(width/10)+160, (j+1)*tileSize+(height/10));
        else
            (*(p1+i)).setPosition((i%20)*tileSize+(width/10)+160, j*tileSize+(height/10));
        if(i%20 == 0)
            j++;
    }
    j = 0;
    for(int i = 0; i < numberOfTiles; i ++){
        (*(p2+i)).setSize(Vector2f(tileSize,tileSize));
        if(i%20==0)
            (*(p2+i)).setPosition((i%20)*tileSize+(width/10)+160, (j+1)*tileSize+(height/10));
        else
            (*(p2+i)).setPosition((i%20)*tileSize+(width/10)+160, j*tileSize+(height/10));
        if(i%20 == 0)
            j++;
    }
    j = 0;
    for(int i = 0; i < numberOfTiles; i ++){
        (*(p3+i)).setSize(Vector2f(tileSize,tileSize));
        if(i%20==0)
            (*(p3+i)).setPosition((i%20)*tileSize+(width/10)+160, (j+1)*tileSize+(height/10));
        else
            (*(p3+i)).setPosition((i%20)*tileSize+(width/10)+160, j*tileSize+(height/10));
        if(i%20 == 0)
            j++;
    }
    titleImage.setTexture(&titleImageTexture);
    titleImage.setPosition(width/2-300, height/4 - 450);
    titleImage.setSize(Vector2f(600,250));

    
}

void Map::readLevel(int num){
    std::ifstream iFile;
    char next;
   
    
    
    if(num == 1){
        iFile.open("Level1.txt");
        int i = 0;
        if(iFile.is_open()){
            while(!iFile.eof()){
                iFile >> next;
                if(next == '#'){
                    (*(p1+i)).setTexture(&tileTexture);
                }
                else
                    (*(p1+i)).setFillColor(Color::Black);
                ++i;
            }
        }
        iFile.close();
    }
    else if(num == 2){
        iFile.open("Level2.txt");
        int i = 0;
        if(iFile.is_open()){
            while(!iFile.eof()){
                iFile >> next;
                if(next == '#'){
                    (*(p2+i)).setTexture(&tileTexture);
                }
                else
                    (*(p2+i)).setFillColor(Color::Black);
                ++i;
            }
        }
        iFile.close();
        
    }
    else if(num == 3){
        iFile.open("Level3.txt");
        int i = 0;
        if(iFile.is_open()){
            while(!iFile.eof()){
                iFile >> next;
                if(next == '#'){
                    (*(p3+i)).setTexture(&tileTexture);
                }
                else
                    (*(p3+i)).setFillColor(Color::Black);
                ++i;
            }
        }
        iFile.close();
        
    }
    
}

void Map::drawLevel(RenderWindow& window,int level){
    
    
    readLevel(level);
    window.draw(titleImage);
    
    
    if(level == 1)
        for(int i = 0; i < numberOfTiles; i++)
            window.draw(*(p1+i));
    if(level == 2)
        for(int i = 0; i < numberOfTiles; i++)
            window.draw(*(p2+i));
    if(level == 3)
        for(int i = 0; i < numberOfTiles; i++)
            window.draw(*(p3+i));

}
RectangleShape* Map::sendMap(int num){
    if(num == 1)
        return p1;
    if(num == 2)
        return p2;
    if(num == 3)
        return p3;
}

void Map::updateLevelNumber(String str){
    levelNumber = str;
}
String Map::getLevelNumber(){
    return levelNumber;
}


