#ifndef TRIVIA_H
#define TRIVIA_H
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

class Trivia
{
public:
    Trivia();
    int readQandA(string fileName); // fills arrays of questions and answers
    int readOptions(string fileName); // fills array of multiple choice options
    int locationQuestion(); // returns random index of question to be asked between [0,9]
    void correctOrNo(int index, string userAnswer); 

    string getQuestionAt(int index) const;
    string getAnswerAt(int index) const;
    void displayTriviaStats() const; // displays how many questions have been asked and average score so far
    void displayQuestionOption(int index) const; // displays question and a b c options 

private:
    int score;
    int NumOfQsAsked; // number of questions asked
    vector<int> indexOfQuesAsked = {999}; // keeps track of which questions have been asked. 999 is a dummy value
    string questions[10];
    string answers[10];
    string options[30];
};
#endif