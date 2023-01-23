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
#include "ffGame.h"
using namespace std;

int split (string inputString, char separator, string arr[], int size); 

/* if user enters multiple strings for an intended cin >> integer variable (for example),
this clears the input for the next cin to function correctly */
void inputvalid()
{
    cin.clear();
    string item;
    getline(cin,item);
}


Game::Game()
{
    didntEat1 = true;
    didntEat2 = true;
    didntEat3 = true;
    didntEat4 = true;
    didntMakeFood = true;
    money = 50.00; 
    ingredCount = 0;
    finalScore = 0;
    energyPointsTotal = 0;
    confidencePointsTotal = 0;
    focusPointsTotal = 0; 
    gymPoints = 0;
    didntDoTreadmill = true;
}

void Game::displayStats() const 
{
    // final score takes into account food points, gym points, map points
    cout << endl << "Your final score will be calculated at the end, but so far:" << endl;
    cout << fixed << setprecision(2) << endl;
    cout << "In the Food category, you have" << endl << "    $" << money << " left, " << endl << "    " <<
    focusPointsTotal << " net Food focus point(s), " << energyPointsTotal << " net Food energy point(s), and " <<
    confidencePointsTotal << " net Food confidence point(s)." << endl;

    cout << "In the Gym category, you have" << endl << "    trained for " << myGym.getTimeTrained() << " mins," << endl << "    " <<
    myGym.getHealth() << " Gym health point(s), and " << myGym.getPreparation() << " Gym preparation point(s)." << endl;

    cout << "In the Compete (Map) category, you will start with 50 points and that score will be available once you complete the game." << endl << endl;
} 

void Game::updateFinalScore(double points)
{
    finalScore = finalScore + points;
}

double Game::getFinalScore() const
{
    return finalScore;
}

void Game::addFocus(int points)
{
    focusPointsTotal = focusPointsTotal + points;
}
int Game::getFocus() const
{
    return focusPointsTotal;
}

void Game::addEnergy(int points)
{
    energyPointsTotal = energyPointsTotal + points;
}
int Game::getEnergy() const
{
    return energyPointsTotal;
}

void Game::addConfidence(int points)
{
    confidencePointsTotal = confidencePointsTotal + points;
}
int Game::getConfidence() const
{
    return confidencePointsTotal;
}


////////// functions associated with Food class //////////
void Game::ingredientsListMenu()
{
    cout << endl << "What should I buy? " << endl << endl <<
    "First, press j to see what ingredients you need." << endl << 
    "Add one ingredient at a time (order doesn't matter); only get your required ingredients." << endl <<
    "You only need 1 of each required ingredient. If you buy more than 1, your money will decrease after you make food." << endl <<
    "Your money will be updated once you have bought all your ingredients or if you make a mistake." << endl <<
    "*** Once you have all your ingredients, press k!!! ***" << endl << endl <<
    "a. 1 carrot " << endl << "b. 1 zucchini " << endl << "c. 1 tomato " << endl <<
    "d. 1 marinara can " << endl << "e. 1 noodle pack " << endl << "f. 1 lettuce " << endl <<
    "g. 1 bun" << endl << "h. 1 rice bag " << endl << "i. View current bought items & how many points/ money I have" << endl <<
    "j. View what ingredients I need" << endl << "k. MAKE FOOD!!" << endl << "l. Exit" << endl;
}

void Game::gatherIngredients(char choice, vector<string>& myVec) // vector initially empty. you add ingredients to it
{
    cout << endl;
    if (didntMakeFood == false)
    {
        if (choice != 'l') // 'l' is exit
        {
            cout << "You already made food! Do something else. Press l to exit" << endl;
        }
        return;
    }
    if (choice >= 97 && choice <= 104) // ingredient selected (letters a thru h)
    {
        // check to see if you have enough money
        if (!enoughMoney(FoodObject[4].getPrice())){ // the amount in the txt file is the total cost needed to make food
            cout << "You don't have enough money to make food." << endl;
        }
        else
        {
            bool notFound = true;
            string ingred = charToWord(choice);
            // check to see if you need it
            int i = 0;
            while (i < FoodObject[4].getNumberFoodItems() && notFound) // search for all food items in FoodObject[4] (foods in line 5 of the Food.txt files) required to make your recipe
            {
                if (FoodObject[4].getFoodItem(i) == ingred) // correct; means user selected an ingredient needed to make food
                {   
                    myVec.push_back(ingred);
                    ingredCount++; // if you don't buy more ingredients than necessary, you get bonus +2 points in each category. if you buy more ingredients than necessary, money goes down
                    notFound = false;
                    cout << "Great! Bought a " << ingred << "." << endl;
                }
                else
                {
                    i++;
                }
            }
            if (notFound) // you bought an uneeded ingredient
            {
                cout << "You bought an unecessary ingredient. (Confidence -2, money -$5)" << endl;
                addConfidence(-2);
                money = money - 5;
            }
        }
    } 
    else if (choice == 'i') 
    {
        cout << "Current bought items: " << endl;
        for (int i = 0; i < myVec.size(); i++)
        {
            cout << myVec[i];
            if (i != myVec.size() - 1 && i != 0)
            {
                cout << ", ";
            }
        }
        displayStats();

    }
    else if (choice == 'j') // from txt file, get which ingredients needed
    {
        cout << "You need: " << endl;
        for (int i = 0; i < FoodObject[4].getNumberFoodItems(); i++)
        {
            cout << FoodObject[4].getFoodItem(i);
            if (i != FoodObject[4].getNumberFoodItems() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }   
    else if (choice == 'k')
    {
        if (ingredCount < FoodObject[4].getNumberFoodItems()) // ingredCount only incremented if user collected correct ingredient
        {
            cout << "Not enough ingredients to make your food! Add more! (Confidence -1)" << endl;
            addConfidence(-1);
        }
        else
        {
            cout << "Success! You made your own food! (Focus, Energy, & Confidence increased)" << endl;
            addFocus(FoodObject[4].getFocusPointsF());
            addEnergy(FoodObject[4].getEnergyPointsF());
            addConfidence(5);
            didntMakeFood = false;
            if (ingredCount > FoodObject[4].getNumberFoodItems()) // user bought necessary ingredients but bought extra
            {
                cout << "Since you bought more than needed, your money will be decreased by anywhere between $1 to $10." << endl;
                int factor = rand() % 10 + 1;
                money = money - factor;
            }
            else
            {
                cout << "Since you bought the exact amount of needed ingredients, an additional +2 point has been added in all Food categories!" << endl;
                cout << "Your ingredients costed $" << FoodObject[4].getPrice() << ", but as a bonus, anywhere between $1 to $9 will be added back to your balance!" << endl;
                addFocus(2); addEnergy(2); addConfidence(2);
                int factorr = rand() % 10;
                money = money + factorr;
                if (factorr == 0){
                    money = money + 1.00;
                }
            }
            money = money - FoodObject[4].getPrice(); // subtract the amount making food costs after you've successfully made food
        }
    }
    else if (choice == 'l')
    {
        cout << "Bye!" << endl;
    }
    else
    {
        inputvalid();
        cout << "Invalid input. Try again." << endl;
    }
}

// fills array of Food objects (name, price, focus points, energy points assoc w each object)
bool Game::readFoodItems(string fileName)
{
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail())
    {
        return false;
    }

    string line;
    bool notDone = true; 
    int CAPACITY = 100;
    string array[CAPACITY];
    int i = 0;
    while (getline(myFile,line))
    {
        split(line, ',', array, CAPACITY);
        if (i != 4) // lines 1-4 in txt file are food options when you order at restaruant
        {
            FoodObject[i].addFood(array[0]); 
            FoodObject[i].setPrice(stod(array[1])); 
            FoodObject[i].setFocusPointsF(stoi(array[2]));
            FoodObject[i].setEnergyPointsF(stoi(array[3]));
        }
        else // 5th line of file has multiple foods (ingredients to make your own food)
        {
            int j = 0;
            bool notDone = true;
            while (notDone)
            {
                char checkIfNumber = array[j][0]; // first index character of string array[j]
                if (!isdigit(checkIfNumber)) // if it's not a digit, it's a food item
                {
                    FoodObject[4].addFood(array[j]);
                    j++;
                }
                else{ // then it's the price (type double)
                    notDone = false;
                }
            }
            FoodObject[4].setPrice(stod(array[j])); 
            FoodObject[4].setFocusPointsF(stoi(array[j+1]));
            FoodObject[4].setEnergyPointsF(stoi(array[j+2]));
        }
        i++;
    }
    return true;
}

bool Game::enoughMoney(double cost)
{
    if (money - cost >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::orderEntreeMenu()
{
    cout << fixed << setprecision(2) << endl;
    cout << "What entree would you like? (more expensive items means more points, & you can order all the entrees if you want)" << endl <<
    "1. " << FoodObject[0].getFoodItem(0) << " ($" << FoodObject[0].getPrice() << ")" << endl <<
    "2. " << FoodObject[1].getFoodItem(0) << " ($" << FoodObject[1].getPrice() << ")" << endl <<
    "3. " << FoodObject[2].getFoodItem(0) << " ($" << FoodObject[2].getPrice() << ")" << endl <<
    "4. " << FoodObject[3].getFoodItem(0) << " ($" << FoodObject[3].getPrice() << ")" << endl <<
    "5. View how much $ and points I have" << endl << "6. Exit restaurant" << endl;
}

void Game::foodTask(int choice)
{
    cout << endl;
    if (choice == 1) // FoodObject[0] is pizza, grilled cheese, or curry, depending on which Food.txt file read
    {
        if (!enoughMoney(FoodObject[0].getPrice())) 
        {
            cout << "You don't have enough money for " << FoodObject[0].getFoodItem(0) << "." << endl;
        }
        else
        {
            if (didntEat1 == true)
            {
                cout << "Your food comes, but some of it is unhealthily burnt." << endl <<
                "Type \"eat anyways\" to eat the burnt stuff or \"eat around\" to avoid it." << endl;
                inputvalid();
                string input;
                getline(cin,input);
                if (input == "eat around") // correct
                {
                    cout << "You savor the flavors while eating around the burnt areas. (Focus & Energy increased)" << endl;
                    addFocus(FoodObject[0].getFocusPointsF());  
                    addEnergy(FoodObject[0].getEnergyPointsF());
                }
                else
                {
                    cout << "Your mind is somewhere else & you eat the burnt stuff! (Focus decreased, Energy increased [since you ate])" << endl;
                    int subtract = FoodObject[0].getFocusPointsF() * -1;
                    addFocus(subtract);  
                    addEnergy(FoodObject[0].getEnergyPointsF());
                }
                money = money - FoodObject[0].getPrice();
                didntEat1 = false;
            }
            else{
                cout << "You already ate " << FoodObject[0].getFoodItem(0) << ". Eat something else or exit the restaurant." << endl;
            }
        }
        cout << endl << endl;
    }
    else if (choice == 2) // salad, salmon & rice, or chicken alfredo
    {
        if (!enoughMoney(FoodObject[1].getPrice())) 
        {
            cout << "You don't have enough money for " << FoodObject[1].getFoodItem(0) << "." << endl;
        }
        else
        {
            if (didntEat2 == true)
            {
                cout << "Your food comes, but a fly just landed it!" << endl <<
                "Type the next number in this pattern to scare it off with your critical thinking skills:" << endl;
                cout << "9 1 8 2 7 3 6 __" << endl;
                int input1;
                cin >> input1;
                if (input1 == 4) // correct
                {
                    cout << "Correct! You swat the fly away and enjoy eating your entree. (Focus & Energy increased)" << endl;
                    addFocus(FoodObject[1].getFocusPointsF());   
                    addEnergy(FoodObject[1].getEnergyPointsF());
                }
                else
                {
                    cout << "Incorrect. When swatting the fly away, you miss and spill your drink. (Focus decreased, Energy increased [since you ate])" << endl;
                    int subtract1 = FoodObject[1].getFocusPointsF() * -1;
                    addFocus(subtract1);   
                    addEnergy(FoodObject[1].getEnergyPointsF());
                }
                inputvalid();
                money = money - FoodObject[1].getPrice();
                didntEat2 = false;
            }
            else{
                cout << "You already ate " << FoodObject[1].getFoodItem(0) << ". Eat something else or exit the restaurant." << endl;
            }
        }
        cout << endl << endl;
    }
    else if (choice == 3) // mud, rocks, or trash
    {
        if (!enoughMoney(FoodObject[2].getPrice())) 
        {
            cout << "You don't have enough money for " << FoodObject[2].getFoodItem(0) << "." << endl;
        }
        else
        {
            if (didntEat3 == true)
            {
                cout << "The waiter says "<<  FoodObject[2].getFoodItem(0) << " is on there by mistake but still takes your money. Order again! (Focus & Energy decreased)" << endl;
                addFocus(FoodObject[2].getFocusPointsF());
                addEnergy(FoodObject[2].getEnergyPointsF());
                didntEat3 = false;
            }
            else
            {
                cout << "You already tried ordering this! Why are you ordering it again? (Focus decreased)" << endl;
                addFocus(FoodObject[2].getFocusPointsF());
            }
            money = money - FoodObject[2].getPrice(); // money decreased every time user selects this choice
        }
        cout << endl << endl;
    }
    else if (choice == 4) // orange chicken, pho, or dumplings
    {
        if(!enoughMoney(FoodObject[3].getPrice()))
        {
            cout << "You don't have enough money for orange chicken." << endl;
        }
        else
        {
            if (didntEat4 == true)
            {
                char foood;
                cout << "You start eating, but it's too hot! To cool yourself down, you reach for..." << endl;
                do {
                    cout << "a. Sriracha" << endl << "b. Wasabi" << endl << "c. Water" << endl;
                    cin >> foood;

                    if (foood == 'a') 
                    {
                        cout << "The sriracha makes it worse! (Focus decreased, Energy increased [since you ate])" << endl;
                        int subtract2 = FoodObject[3].getFocusPointsF() * -1;
                        addFocus(subtract2);   
                        addEnergy(FoodObject[3].getEnergyPointsF());                        
                    }
                    else if (foood == 'b')
                    {
                        cout << "The wasabi makes it worse! (Focus decreased, Energy increased [since you ate])" << endl;
                        int subtract3 = FoodObject[3].getFocusPointsF() * -1;
                        addFocus(subtract3);   
                        addEnergy(FoodObject[3].getEnergyPointsF());   
                    }
                    else if (foood == 'c')
                    {
                        cout << "The water neutralizes the hot temperature of the chicken and you proceed eating. (Focus & Energy increased)" << endl;
                        addFocus(FoodObject[3].getFocusPointsF());
                        addEnergy(FoodObject[3].getEnergyPointsF());
                    }
                    else
                    {
                        inputvalid();
                        foood = 'z';
                        cout << "Invalid input. Try again. (Focus -1)" << endl;
                        addFocus(-1);
                    }
                } while (foood != 'a' && foood != 'b' && foood != 'c');
                inputvalid();
                didntEat4 = false;
                money = money - FoodObject[3].getPrice();
            }
            else{
                cout << "You already ate " << FoodObject[3].getFoodItem(0) << ". Eat something else or exit the restaurant." << endl;
            }
        }
        cout << endl << endl;
    }
    else if (choice == 5) // view stats
    {
        displayStats();
    }
    else if (choice == 6) // leave
    {
        cout << "Bye!" << endl << endl;
    }
    else
    {
        inputvalid();
        cout << "Invalid input. Try again" << endl;
    }
}

bool Game::getDidntMakeFood() const
{
    return didntMakeFood;
}

// for the make your own food option menu. returns the food item assoc w/ the string
string Game::charToWord (char character) 
{
    switch (character)
    {
        case 'a': return "carrot"; break;
        case 'b': return "zucchini"; break;
        case 'c': return "tomato"; break;
        case 'd': return "marinara"; break;
        case 'e': return "noodle pack"; break;
        case 'f': return "lettuce"; break;
        case 'g': return "bun"; break;
        case 'h': return "rice bag"; break;
        default: return ""; break;
    }
}



/////////// functions associated with Gym class ///////////

int Game::trainTime() // returns the minutes trained
{
    double input = 0; // initialized to 0 to enter the do-while loop, but this value will change based on user input
    do
    {
        cout <<  "How many minutes do you want to do run for?" << endl <<
        "(enter 120 mins or less to avoid burnout & 30 mins or more to be prepared)" << endl;
        cin >> input;
        if (cin.fail() || input <= 0)
        {
            inputvalid();
            input = -1;
            cout << "Enter a positive time." << endl;
        }
    } while (input <= 0);
    return input;
} 
void Game::treadmill()
{
    cout << endl;
    if (didntDoTreadmill) // can only do it once per play
    {
        int timeTrained = trainTime();
        myGym.setTimeTrained(timeTrained);// updates the time trained data member
        inputvalid();
        string running;
        cout << "Run 3 laps! Input vnvnvnvnvnvnvnvnvnvn (vn x10) to stimulate running." << endl;
        getline(cin,running);
        if (running == "vnvnvnvnvnvnvnvnvnvn")
        {
            cout << "You successfully ran 3 laps! (Preparation & Health increased heavily)" << endl;
            myGym.setPreparation(10.5);
            myGym.setHealth(6);
        }
        else // see how many characters the input is off by; numberOfN & numberofV should be 10 each
        {
            int numberOfN = 0;
            int numberofV = 0;
            for (int i = 0; i < running.length(); i++)
            {
                if (running[i] == 'n')
                {
                    numberOfN++;
                }
                if (running[i] == 'v')
                {
                    numberofV++;
                }
            }
            int offBy = abs(10 - numberOfN) + abs(10 - numberofV);
            if (offBy >= 10) // off by a lot
            {
                cout << "Instead of running laps, you did nothing. (Preparation & Health decreased heavily)" << endl;
                myGym.setPreparation(-5.5);
                myGym.setHealth(-5);
            }
            else if (offBy >= 5) // off by 5 to 9 letters
            {
                cout << "You ran 2 out of 3 laps but ran out of energy & had to stop. (Preparation & Health decreased)" << endl;
                myGym.setPreparation(-3.5);
                myGym.setHealth(-2);
            }
            else if (offBy > 0) // off by 1 to 4 letters
            {
                cout << "You ran all 3 laps but got slightly tired towards the end. (Preparation & Health slightly increased)" << endl;
                myGym.setPreparation(2);
                myGym.setHealth(2);
            }
            if (offBy == 0) // means they inputted 10 n and 10 v but in a wrong order
            {
                cout << "You ran 3 laps but ran into a pole. (Preparation & Health slightly increased)" << endl;
                myGym.setPreparation(3);
                myGym.setHealth(3);
            }
        }
        didntDoTreadmill = false;
    }
    else
    {
        cout << "You ready ran! Do something else." << endl;
    }
}

void Game::calcGymPoints()
{
    int factor = rand() % 3 + 1;
    cout << "Side note: ";
    if (myGym.getTimeTrained() < 30 || myGym.getTimeTrained() > 120) // too little/much time trained, randomize the factor u decrease preparation by
    {
        cout << "You either trained too little or too much. Your gym points are not in great standing." << endl;
        gymPoints = (myGym.getPreparation() / factor) + myGym.getHealth() - (myGym.getTimeTrained() * .25);
    }
    else
    {
        cout << "You trained adequately and avoided burnout! Your gym points are in good standing." << endl;
        gymPoints = (myGym.getPreparation() * factor) + myGym.getHealth() + (myGym.getTimeTrained() * 1.5);
    }
    cout << endl;
}
double Game::getGymPoints() const
{
    return gymPoints;
}



//////////////// functions associated with Map class ////////////////

int Game::getMapPoints() const
{
    return myMap.getPoints();
}
/* updates the locations of v by filling in the associated vectors
if bool initial is true, that means user has made on moves yet, so update v location vectors */
void Game::displayChallengeMap(int choice, bool initial)
{
    if (choice == 0) // backwards c shape
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (i == myMap.getX() && j == myMap.getY())
                {
                    cout << "X"; // user's initial position (bottomrrffffffffffffffere right)
                }
                else if (i == 0 || j == 6 || j == 0)
                {
                    cout << "v";
                    if (initial)
                    {
                        myMap.addVLocationX(i); // updates respective vector index storing row # of where 'v' is on the map (the trail user is supposed to follow)
                        myMap.addVLocationY(j); // updates respective vector index storing col # 
                    }
                }
                else
                {
                    cout << "-";
                }
            }
            cout << endl;
        }
    }
    if (choice == 1) // snake-like zigzag pattern
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (i == myMap.getX() && j == myMap.getY())
                {
                    cout << "X"; // initial position
                }
                else if (j <= i && j > i - 2 || j > 4)
                {
                    cout << "v";
                    if (initial)
                    {
                        myMap.addVLocationX(i); // updates respective vector index storing row # of where 'v' is on the map (trail user's supposed to follow)
                        myMap.addVLocationY(j); // updates respective vector index storing col # 
                    } 
                }
                else
                {
                    cout << "-";
                }
            }
            cout << endl;
        }
    }
    if (choice == 2) // makes a "2" shape
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (i == myMap.getX() && j == myMap.getY())
                {
                    cout << "X";
                }
                else if (i % 2 == 0 || i == 1 && j == 6 || i == 3 && j == 0)
                {
                    cout << "v";
                    if (initial)
                    {
                        myMap.addVLocationX(i); // updates respective vector index storing row # of where 'v' is on the map (trail user's supposed to follow)
                        myMap.addVLocationY(j); // updates respective vector index storing col # 
                    }
                }
                else
                {
                    cout << "-";
                }
            }
            cout << endl;
        }
    }
} 

void Game::startChallenge(int choice) 
{
    if (choice == 0)// for round 1 (map 0), X should be initialized to bottom right corner as opposed to the default contructor upper left
    {
        myMap.setX(4);
        myMap.setY(6);
    }
    displayChallengeMap(choice,true); // true would fill up the vectors with row and col locations for v
}

void Game::challenge(int choice)
{
    cout << endl;
    bool notDone = true;
    while (notDone)
    {
        string move;
        cout << "a = left | w = up | s = down | d = right" << endl;
        cin >> move;
        if (move == "a")
        {
            myMap.moveLeft();
            if (myMap.matchOrNo(myMap.getX(), myMap.getY()) == true) // correct
            {
                if (myMap.vectorSize() > 0)
                {
                    cout << "Correct! Keep following the trail of v's" << endl;
                }            
            }
            else
            {
                cout << "Wrong move. Map point -1." << endl;
                myMap.updateMapPoints(-1);
            }
        }   
        else if (move == "w")
        {
            myMap.moveUp();
            if (myMap.matchOrNo(myMap.getX(), myMap.getY()) == true) // correct
            {
                if (myMap.vectorSize() > 0)
                {
                    cout << "Correct! Keep following the trail of v's" << endl;
                }
            }
            else
            {
                cout << "Wrong move. Map point -1." << endl;
                myMap.updateMapPoints(-1);
            }
        }
        else if (move == "s")
        {
            myMap.moveDown();
            if (myMap.matchOrNo(myMap.getX(), myMap.getY()) == true) // correct
            {
                if (myMap.vectorSize() > 0)
                {
                    cout << "Correct! Keep following the trail of v's" << endl;
                }            
            }
            else
            {
                cout << "Wrong move. Map point -1." << endl;
                myMap.updateMapPoints(-1);
            }
        }
        else if (move == "d")
        {
            myMap.moveRight();
            if (myMap.matchOrNo(myMap.getX(), myMap.getY()) == true) // correct
            {
                if (myMap.vectorSize() > 0)
                {
                    cout << "Correct! Keep following the trail of v's" << endl;
                }
            }
            else
            {
                cout << "Wrong move. Map point -1." << endl;
                myMap.updateMapPoints(-1);
            }
        }
        else
        {
            inputvalid();
            cout << "Invalid input. Try again." << endl;
        }

        if (myMap.vectorSize() == 0) // no more v's on the map; user completed the round
        {
            cout << "You've reached the end! Good job!" << endl; // onto the next round if user is on round 1 or 2
            myMap.reset(); // so for other rounds, the vLocationX and vLocationY are cleared and filled depending on the map layout
            if (choice == 2) // last round (round 3)
            {
                cout << "Congratulations on completing the game! Open out.txt to see your stats." << endl;
            }
            notDone = false;
        }
        else
        {
            displayChallengeMap(choice, false);
        }
        cout << endl;
    }
}



// split function from past homework
int split (string inputString, char separator, string arr[], int size)
{
    // count how many delimeters there are in inputString
    int delimeterCount = 0;
    for (int i = 0; i < inputString.length(); i++)
    {
        char ch = inputString[i];
        if (ch == separator)
        {
            delimeterCount++;
        }
    }

    int count = 0; // index position of arr
    int pos = 0;
    for (int i = 0; i < inputString.length(); i++)
    {  
        char ch = inputString[i];
        if (ch == separator)
        {
            if (count < size)
            {
                arr[count] = inputString.substr(pos, i - pos); // isolate and index the non-delimeter element
                count++;
                pos = i + 1; // add 1 to account for delimeter's position
                if (count >= size) // would update array until array houses the max amount of elements permitted
                {
                    return -1;
                }
                if (count == delimeterCount) // the last array value
                {
                    arr[count] = inputString.substr(i + 1); // no other delimeters or elements after
                }
            }
        }
    }
    if (inputString == "")
    {
        return 0;
    }
    if (count == 0) // no delimeter match found
    {
        arr[0] = inputString; 
        return 1;
    }
    return count + 1; 
} 