#ifndef FGYM_H
#define FGYM_H
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

class Gym
{
public:
    Gym();

    void setPreparation(double amount);
    double getPreparation() const;

    void setHealth(int amount);
    int getHealth() const;

    void setTimeTrained(double amount);
    double getTimeTrained() const;

private:
    double preparation;
    int health;
    double timeTrained; 
};
#endif