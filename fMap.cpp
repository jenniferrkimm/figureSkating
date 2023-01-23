#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "fMap.h"
using namespace std;

Map::Map()
{
    x = 0; // row
    y = 0; // col
    mapScore = 50; // every wrong move subtracts 1 
}

void Map::updateMapPoints(int point)
{
    mapScore = mapScore + point;
}
int Map::getPoints() const
{
    return mapScore;
}
void Map::moveRight()
{
    if (y < 6)
    {
        y++;
    }
    else
    {
        cout << "Can't move right." << endl;
    }
}
void Map::moveLeft()
{
    if (y > 0)
    {
        y--;
    }
    else
    {
        cout << "Can't move left." << endl;
    }
}
void Map::moveUp()
{
    if (x > 0)
    {
        x--;
    }
    else
    {
        cout << "Can't move up." << endl;
    }
}
void Map::moveDown()
{
    if (x < 4)
    {
        x++;
    }
    else
    {
        cout << "Can't move down." << endl;
    }
}
void Map::setX(int xVal)
{
    x = xVal;
}
void Map::setY(int yVal)
{
    y = yVal;
}
int Map::getX() const
{
    return x;
}
int Map::getY() const
{
    return y;
}

// adds row location of the v's to the vector vLocationX data member
void Map::addVLocationX(int xCoord)
{
    vLocationX.push_back(xCoord);
}
// adds col location of the v's to the vector vLocationX data member
void Map::addVLocationY(int yCoord)
{
    vLocationY.push_back(yCoord);
}

// returns row location of the v at an index
int Map::getVLocationX(int index)
{
    return vLocationX[index];
}
// returns col location of the v at an index
int Map::getVLocationY(int index)
{
    return vLocationY[index];
}

int Map::vectorSize()
{
    return vLocationX.size();
}
// traverse vLocationX vLocationY to see if user moved to a location with v present
bool Map::matchOrNo(int userXCoord, int userYCoord)
{
    if (vLocationX.size() == 0 || vLocationY.size() == 0)
    {
        return false; // impossible to find match if those are empty
    }

    // traverse vLocationX & vLocationY vector indexes to see if userXCoord & userYCoord matches
    int i = 0;
    while (i < vLocationX.size())
    {
        // see if at the same i index, vLocationY matches userYCoord
        if (vLocationX[i] == userXCoord && vLocationY[i] == userYCoord)  // match!
        {
            // make sure user has only visited that coordinate once. At index i, delete the value in vLocationX and vLocationY
            vLocationX.erase(vLocationX.begin() + i);
            vLocationY.erase(vLocationY.begin() + i);
            return true;
        }
        else
        {
            i++;
        }
    }
    return false; 
}

void Map::reset()
{
    vLocationX.clear();
    vLocationY.clear();
    x = 0;
    y = 0;
}