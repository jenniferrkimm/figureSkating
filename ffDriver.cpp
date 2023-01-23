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

/* if user enters multiple strings for an intended cin >> integer variable (for example),
this clears the input for the next cin to function correctly */
void inputvalidd()
{
    cin.clear();
    string item;
    getline(cin,item);
}

int main()
{
///////////// INITIALIZING /////////////

    Game test;
    srand(time(0));
    int randNumber = rand() % 3; // 33% chance of reading from the 3 files
    string readFromThisFile;
    
    /* when you order from restaurant, your menu is randomized between Food1,Food2,Food3 txt files at compile time.
    each txt file has different food options with different prices and different points associated with them */
    if(randNumber == 0)
    {
        readFromThisFile = "Food1.txt"; 
    }
    if(randNumber == 1)
    {
        readFromThisFile = "Food2.txt";
    }
    if(randNumber == 2)
    {
        readFromThisFile = "Food3.txt"; 
    }
    test.readFoodItems(readFromThisFile);
    vector<string> myVecTest; // ingredients user has
    myVecTest.push_back(""); // so it has a size of 1 to avoid seg fault with gatherIngredients

    bool notDoneFinal = true;

///////////// GAME START /////////////
    string name;
    cout << "Enter your first name:" << endl;
    cin >> name;
    inputvalidd();
    string pushEnter;
    cout << "Hello " << name << ", welcome to Figure Skating. Press enter to continue" << endl;
    getline(cin,pushEnter);
    cout << "In this game, you will get to play as a figure skater competing at the Olympics!" << endl << "Ready?" << endl;
    getline(cin,pushEnter);

    while (notDoneFinal)
    {
        int mainInput;
        cout << endl << "Before competing, you should explore options 2 & 3 to maximize total points at the end." << endl;
        cout << "Menu: " << endl << "1. Read rules" << endl << "2. Eat" << endl << "3. Exercise" << endl <<
        "4. Play trivia for fun (doesn't impact final score)" << endl << "5. Compete!" << endl << "6. View current stats" << endl << "7. Quit" << endl;
        cin >> mainInput;
        cout << endl;
        if (mainInput == 1) // read rules
        {
            cout << "The only thing to really know is that competing (option 5) results in the end of the game, so you can't go back to visit other menu options." << endl <<
            "Also, you earn points from eating, exercising, and competing, and your final score is calculated after you compete." << endl;
            cout << "Would you like to see the detailed rules? press 1 if yes and anything else if no:" << endl;
            int input;
            cin >> input;
            if (input == 1)
            {
                ifstream ruleFile;
                ruleFile.open("rules.txt");
                string rulesLines;
                while (getline(ruleFile,rulesLines))
                {
                    cout << rulesLines << endl;
                }
            }
            inputvalidd();
            cout << endl << endl;
        }
        else if (mainInput == 2) // eat
        {
            bool notDoneEat = true;
            while (notDoneEat)
            {
                cout << "1. Order at a restaurant" << endl << "2. Make my own food" << endl <<
                "3. Go back to main menu." << endl << "4. View stats" << endl;
                int foodChoice;
                cin >> foodChoice;
                switch (foodChoice)
                {
                    case 1: // restaurant
                    {
                        bool notDone = true;
                        while (notDone)
                        {
                            test.orderEntreeMenu();
                            int input;
                            cin >> input;
                            test.foodTask(input);
                            if (input == 6){
                                notDone = false;
                            }
                        }
                        break;
                    } 
                    case 2: // make your own food
                    {
                        cout << endl << "You walk over to the nearest grocery store..." << endl;
                        bool notDone2 = true;
                        while (notDone2)
                        {
                            test.ingredientsListMenu();
                            char input;
                            cin >> input;
                            test.gatherIngredients(input,myVecTest);
                            if (input == 'l' || (input == 'k' && test.getDidntMakeFood() == false))
                            {
                                notDone2 = false; // meaning user pressed quit or already made food
                            }
                        } 
                        break;
                    }
                    case 3: // back to main menu
                    {
                        notDoneEat = false; break;
                    }
                    case 4: test.displayStats(); break;
                    default:
                    {
                        inputvalidd();
                        cout << "Invalid input. Try again." << endl; break;
                    }
                }
            }
        }
        else if (mainInput == 3) // gym
        {
            bool notDoneGym = true;
            while (notDoneGym)
            {
                cout << "1. Treadmill" << endl << "2. View stats" << endl << "3. Go back to main menu" << endl;
                int gymChoice;
                cin >> gymChoice;
                switch(gymChoice)
                {
                    case 1: // treadmill
                    {
                        test.treadmill();
                        break;
                    }
                    case 2:
                    {
                        test.displayStats(); break;
                    }
                    case 3:
                    {
                        notDoneGym = false; break;
                    }
                    default:
                    {
                        inputvalidd();
                        cout << "Invalid input. Try again." << endl; break;
                    }
                }
            }
        }
        else if (mainInput == 4) // trivia
        {
            bool notDoneTrivia = true;
            while (notDoneTrivia)
            {
                string triviaInput;
                cout << "Which trivia do you want to play?" << endl << 
                "Each option has 10 questions to answer, and you can play them as much as you'd like!" << endl << "a. Guess that skater" << endl <<
                "b. General skating trivia" << endl << "c. Back to main menu" << endl;
                cin >> triviaInput;
                if (triviaInput == "a")
                {
                    cout << endl << "You picked: guess that skater" << endl << endl;
                    Trivia test1;
                    test1.readQandA("skaters.txt");
                    test1.readOptions("skaters.txt");
                    for (int i = 0; i < 10; i++)
                    {
                        int indexx = test1.locationQuestion();
                        if (indexx != -1) // still more questions to ask
                        {
                            test1.displayQuestionOption(indexx);
                            string input;
                            cin >> input;
                            inputvalidd();
                            test1.getAnswerAt(indexx);
                            test1.correctOrNo(indexx, input);
                            cout << indexx << endl;
                            test1.displayTriviaStats();
                        }
                        else
                        {
                            cout << "You've already answered all the questions!" << endl;
                        }
                    }
                }
                else if (triviaInput == "b")
                {
                    cout << endl << "You picked: general skating trivia" << endl << endl;
                    Trivia test2;
                    test2.readQandA("generalSkating.txt");
                    test2.readOptions("generalSkating.txt");
                    for (int i = 0; i < 10; i++)
                    {
                        int indexx = test2.locationQuestion();
                        if (indexx != -1) // still more questions to ask
                        {
                            test2.displayQuestionOption(indexx);
                            string input;
                            cin >> input;
                            inputvalidd();
                            test2.getAnswerAt(indexx);
                            test2.correctOrNo(indexx, input);
                            cout << indexx << endl;
                            test2.displayTriviaStats();
                        }
                        else
                        {
                            cout << "You've already answered all the questions!" << endl;
                        }
                    }
                }
                else if (triviaInput == "c")
                {
                    notDoneTrivia = false;
                }
                else
                {
                    inputvalidd();
                    cout << "Invalid input Try again" << endl;
                }
            }
        }
        else if (mainInput == 5) // compete (uses Map class)
        { // check if user ate and exercised
            int rounds = 0; // 3 rounds total 
            cout << "You're ready to compete! There are 3 rounds. Skate the path of the v pattern to maximize points!" << endl <<
            "Only skate to each v location once (i.e just follow the path)." << endl;
            while (rounds < 3)
            {
                cout << "Here is round " << rounds + 1 << "'s map. Your current position is X." << endl;
                test.startChallenge(rounds); // 0 is round 1
                test.challenge(rounds);
                rounds++;
            }
            ofstream outFile;
            outFile.open("out.txt");
        
        // Calculating total points...
        // total point accumulated with Food class (categories have multipliers)
            double foodTotalScore = test.getConfidence() * 1.5 + test.getEnergy() * 2 + test.getFocus() * 3;
            test.updateFinalScore(foodTotalScore);

        // total points accumulated with Gym class
            test.calcGymPoints(); //calculate points first
            double gymTotalScore = test.getGymPoints();
            test.updateFinalScore(gymTotalScore); // update score

        // total points accumulated with Map class
            int mapTotalScore = test.getMapPoints();
            test.updateFinalScore(mapTotalScore);

            outFile << "Calculating total points for " << name << endl << "Your total score is " << test.getFinalScore() << endl <<
            "You earned " << foodTotalScore << " Food points, " << gymTotalScore << " Gym points, and " << mapTotalScore << " Map points" << endl;
            notDoneFinal = false;
        }
        else if (mainInput == 6)
        {
            test.displayStats();
        }
        else if (mainInput == 7)
        {
            cout << "Bye!" << endl;
            notDoneFinal = false;
        }
        else
        {
            inputvalidd();
            cout << "Invalid input. Try again" << endl;
        }
    } 
    return 0;
}