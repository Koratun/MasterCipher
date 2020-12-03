#pragma once

#include<iostream>
#include<vector>

using namespace std;

//Function prototypes

//Prints the question and then gets the user's response as a string.
string stringQuestion(string question);
//Prints the question and then gets the user's response as an int. Takes a range of acceptable responses.
int intQuestion(string question, int large, int small = 1);
//Prints the question and then gets the user's response as a boolean.
bool yesNoQuestion(string question);
//Clears the cin buffer so that dangling data from the user's input does not affect the rest of the program.
void clearCinBuffer();
//Splits a string with the given delimiter and returns the list of strings as a vector.
vector<string> splitString(string toSplit, string delimiter);