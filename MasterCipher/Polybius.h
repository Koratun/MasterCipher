#pragma once

#include "Cipher.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

//The Polybius Square class
class Polybius : public Cipher
{
public:
	Polybius();
	Polybius(int layout);
	Polybius(string layoutName);
	//Returns a string form of the encryption key, must be overriden in each child class.
	string virtual getKey();
	//Encodes the message
	string virtual encode(string message);
	//Decodes the message
	string virtual decode(string message);

	//A static member of this class that holds all the premade layouts for the Polybius Square.
	const static string LAYOUTS[5][6];

	//A static constant pointer string array that holds the names of each layout.
	static string* const layoutNames;

private:
	//Lets you know which layout is selected.
	int squareLayout;

	//Displays the Polybius square of the given layout.
	void displayGrid(int layout);
	//Adds the coordinates of the char in the Polybius square to the encoded message variable.			THIS ONE USES A REFERENCE!!
	void addCoordinates(char c, string& encodedMessage);

};