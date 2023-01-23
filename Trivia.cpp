#include <iostream>
#include "Trivia.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

int triviaSplit (string inputString, char separator, string arr[], int size); 

Trivia::Trivia()
{
    score = 0;
    NumOfQsAsked = 0;
}

// fills arrays of questions and answers
int Trivia::readQandA(string fileName)
{
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail())
    {
        return -1;
    }
    else
    {
        string line;
        string array[5];
        int i = 0;
        while (getline(myFile,line))
        {
            int numSplits = triviaSplit(line, ',', array, 5);
            questions[i] = array[0]; // the question is the 1st split index
            answers[i] = array[1]; // the answer is the 2nd split index
            i++;
        }
        return 1;
    }
}

// fills array of multiple choice options
int Trivia::readOptions(string fileName) // separate function from above since i needs to be incremented by 3 for the 3 (a,b,c) options
{
    ifstream myFile;
    myFile.open(fileName);
    if (myFile.fail())
    {
        return -1;
    }
    else
    {
        string line;
        string array[5];
        int i = 0;
        while (getline(myFile,line) && i <= 28)
        {
            int numSplits = triviaSplit(line, ',', array, 5);
            options[i] = array[2];
            options[i+1] = array[3];
            options[i+2] = array[4];
            i = i + 3; // each option is stored in a different index within the options[]
        }
        return 1;
    }
}

// returns random index of question to be asked between [0,9]
int Trivia::locationQuestion()
{
    if (NumOfQsAsked == 11) // 10 + 1 because of dummy value 999
    {
        return -1;
    }
    else // still more questions to be asked
    {
        // to get a random number between 0 and 9 (10 questions in each of the txt files),
        srand(time(0));
        int randomIndex = rand() % 10;
        int i = 0;
        // ensure question to be asked by randomIndex # has not already been asked
        while (i < indexOfQuesAsked.size())
        {
            if (indexOfQuesAsked[i] == randomIndex)
            {
                randomIndex = rand() % 10; // get a new number (question has already been asked)
                i = 0; // reset linear index search
            }
            else if (indexOfQuesAsked[i] != randomIndex && i == indexOfQuesAsked.size() - 1)
            {
                break; // linear search completed; question hasnt been asked yet
            }
            else
            {
                i++; // if i != indexOfQuesAsked.size() - 1, keep cycling through 
            }
        }
        NumOfQsAsked++;
        indexOfQuesAsked.push_back(randomIndex);
        return randomIndex;
    }
}

void Trivia::correctOrNo(int index, string userAnswer)
{
    if (answers[index] == userAnswer)
    {
        cout << "Correct!" << endl;
        score++;
    }
    else
    {
        cout << "Incorrect. The answer is " << answers[index] << "." << endl;
    }
}

string Trivia::getQuestionAt(int index) const
{
    return questions[index];
}
string Trivia::getAnswerAt(int index) const
{
    return answers[index];
}

// displays how many questions have been asked and average score so far
void Trivia::displayTriviaStats() const
{
    cout << endl;
    cout << "You've answered " << NumOfQsAsked << "/10 available questions." << endl;
    cout << fixed << setprecision(1);
    cout << "Your average is " << (score * 1.0 / NumOfQsAsked) * 100 << "%" << endl << endl;
}

// displays question and a b c options 
void Trivia::displayQuestionOption(int index) const
{
    int optionsIndex = index * 3;
    if (optionsIndex != 0) // if index = 1, that's the 2nd question (stored at questions[1]), and the a,b,c options would start at options[3]
    {
        cout << questions[index] << endl << options[optionsIndex] << endl << options[optionsIndex + 1] << endl << options[optionsIndex + 2] << endl;
    }
    else
    {
        cout << questions[0] << endl << options[0] << endl << options[1] << endl << options[2] << endl;
    }
}

// split function
int triviaSplit (string inputString, char separator, string arr[], int size)
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