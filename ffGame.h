#ifndef GAMEF_H
#define GAMEF_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include "fFood.h"
#include "fGym.h"
#include "Trivia.h"
#include "fMap.h"
class Game 
{
public: 
    Game();
    void displayStats() const; 
    void updateFinalScore(double points); 
    double getFinalScore() const;

// transfer the Food points user earns to Game points (the int points parameter is from Food object)
    void addFocus(int points); 
    int getFocus() const;

    void addEnergy(int points);
    int getEnergy() const;
    
    void addConfidence(int points);
    int getConfidence() const;

// functions associated with Food class
    void ingredientsListMenu(); 
    void gatherIngredients(char choice, vector<string>& myVec); 
    bool readFoodItems(string fileName); // populates food items and stats associated with them 
    bool enoughMoney(double cost); // enough money to buy food? standalone????
    void orderEntreeMenu(); // ex) displays menu like: pizza salad mud chicken 
    void foodTask(int choice);
    bool getDidntMakeFood() const;
    string charToWord(char character);

// functions associated with Gym class
    int trainTime();
    void treadmill();

    void calcGymPoints();// do after user completed treadmill
    double getGymPoints() const;

// functions associated with Map class
    int getMapPoints() const;
    void displayChallengeMap(int choice, bool initial); // different map depending on what choice is
    void startChallenge(int choice); // start w 50 points and this will decrease per every wrong move
    void challenge(int choice);

private:
    bool didntEat1;
    bool didntEat2;
    bool didntEat3;
    bool didntEat4;
    bool didntMakeFood; 
    double money; // start with $50
    vector<string> myIngredients;
    int ingredCount;
    const static int foodSize = 5;
    Food FoodObject[foodSize]; 
    int focusPointsTotal; // adds focus points earned from Food activity to the Game object
    int energyPointsTotal; // adds energy points earned from Food to Game object
    int confidencePointsTotal; // adds confidence points earned from Food to Game object
    double finalScore;

    Gym myGym;
    double gymPoints;
    bool didntDoTreadmill;

    Map myMap;
};
#endif