#ifndef FMAP_H
#define FMAP_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class Map
{
public:
    Map(); // position initialized to upper left corner
    void updateMapPoints(int point);
    int getPoints() const;

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    
    void setX(int xVal); 
    void setY(int yVal);
    int getX() const;
    int getY() const;

    void addVLocationX(int xCoord); // adds row location of the v's to the vector vLocationX data member
    void addVLocationY(int yCoord); // adds column location of the v's to the vector vLocationX data member
    int getVLocationX(int index); // returns row location of the v at an index
    int getVLocationY(int index); // returns col location of the v at an index
    int vectorSize();

    bool matchOrNo(int userXCoord, int userYCoord); // traverse vLocationX vLocationY to see if user moved to a location with v present
    void reset(); // clears vLocationX & vLocationY each round (3 rounds total)

private:
    int x; // your current row position
    int y; // your current col position
    int mapScore; // will be added to totalScore in Game class
    vector<int> vLocationX; // stores row number of each v
    vector<int> vLocationY; // stores col number of each v
};
#endif