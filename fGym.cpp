#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "fGym.h"
using namespace std;

Gym::Gym()
{
    preparation = 0;
    health = 0;
    timeTrained = 0;
}

void Gym::setPreparation(double amount)
{
    preparation = preparation + amount;
}
double Gym::getPreparation() const
{
    return preparation;
}

void Gym::setHealth(int amount)
{
    health = health + amount;
}
int Gym::getHealth() const
{
    return health;
}

void Gym::setTimeTrained(double amount)
{
    timeTrained = timeTrained + amount;
    if (timeTrained > 120) // too much, decrease health and preparation here as well as in Game::calcGymPoints 
    {
        cout << "Too long! Health and Preparation decreased." << endl;
        health = health - 3;
        preparation--;
    }
}
double Gym::getTimeTrained() const
{
    return timeTrained;
}