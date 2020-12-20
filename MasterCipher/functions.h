#pragma once

#include "Cipher.h"

#include<iostream>
#include<vector>

using namespace std;

//Function prototypes

//Prints the question and then gets the user's response as a string.
string stringQuestion(string question, string hintMessage = "");
//Prints the question and then gets the user's response as an int. Takes a range of acceptable responses.
int intQuestion(string question, int large, int small = 1, string hintMessage = "");
//Prints the question and then gets the user's response as a boolean.
bool yesNoQuestion(string question);
//Returns if the given char is uppercase (Must be a letter)
bool isUpper(char c);
//Returns if the given char is lowercase (Must be a letter)
bool isLower(char c);
//Returns if the char is a letter
bool isLetter(char c);
//Converts an uppercase char to a lowercase char using references.
void toLower(char& c);
//Splits a string with the given delimiter and returns the list of strings as a vector.
vector<string> splitString(string toSplit, string delimiter);
//Creates a user-define cipher
//Initialize the appropriate cipher and return its address with the 'new' command.
Cipher* createCipher(int which);
//Lists the available ciphers and their descriptions.
void listCiphers();
//A function that lets you rerun the loop part of the level.
void playLevelLoop(string answer, string encryptedMessage, string hint);