#pragma once

#include "Cipher.h"
#include<iostream>
#include<string>

using namespace std;

//The Caeser's Cipher class
class Caesar : public Cipher
{
public:
	Caesar();
	//Create a cipher based on the given key
	Caesar(int key);
	//Create a child cipher and ignore this class's code
	Caesar(string name);
	//Returns a string form of the encryption key, must be overriden in each child class.
	string virtual getKey();
	//Encodes the message
	string virtual encode(string message);
	//Decodes the message
	string virtual decode(string message);

protected:
	//The amount to translate the message through the alphabet.
	int translationAmount;
	//Returns the encoded value of the given letter value where A=1. Simply multiply translationAmount by -1 and run this method again to get the decoded value.
	char getCodedLetterValue(char letterValue);
};