#ifndef fFOOD_H
#define fFOOD_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Food
{
public:
    Food();

    void addFood(string name);
    string getFoodItem (int index) const;
    int getNumberFoodItems() const; // how many food items you currently have

    void setPrice(double price);
    double getPrice() const;

    void setEnergyPointsF(int points);
    int getEnergyPointsF() const;

    void setFocusPointsF(int points);
    int getFocusPointsF() const;

    void setConfidencePointsF(int points);
    int getConfidencePointsF() const;

    double getTotalPointsF() const; // TOTAL POINTS EARNED in food category to be added to final score
private:
    vector<string> foodName; // stores names of the foods
    double foodPrice;
    int energyPointsF;
    int focusPointsF;
    int confidencePointsF;
};
#endif