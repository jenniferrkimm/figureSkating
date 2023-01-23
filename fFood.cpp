#include <iostream>
#include <vector>
#include <string>
#include "fFood.h"
using namespace std;

Food::Food()
{
    energyPointsF = 0;
    focusPointsF = 0;
    confidencePointsF = 0;
}

void Food::addFood(string name)
{
    foodName.push_back(name);
}
string Food::getFoodItem (int index) const
{
    return foodName[index];
}
// how many food items you currently have
int Food::getNumberFoodItems() const
{
    return foodName.size();
}

void Food::setPrice(double price)
{
    foodPrice = price;
}
double Food::getPrice() const
{
    return foodPrice;
}

void Food::setEnergyPointsF(int points)
{
    energyPointsF = energyPointsF + points;
}
int Food::getEnergyPointsF() const
{
    return energyPointsF;
}

void Food::setFocusPointsF(int points)
{
    focusPointsF = focusPointsF + points;
}
int Food::getFocusPointsF() const
{
    return focusPointsF;
}

void Food::setConfidencePointsF(int points)
{
    confidencePointsF = confidencePointsF + points;
}
int Food::getConfidencePointsF() const
{
    return confidencePointsF;
}

double Food::getTotalPointsF() const // multiplier factored in
{
    return focusPointsF * 2 + energyPointsF * 1.5 + confidencePointsF * 1.3;
}