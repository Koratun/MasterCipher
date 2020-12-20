#pragma once

#include<iostream>
#include<string>

using namespace std;

//A Base cipher class that all other ciphers will be derived from. This is also the Morse Code cipher class.
class Cipher
{
public:
	Cipher();
	Cipher(string name);
	//Gets the name of this cipher
	string getName();
	//Returns a string form of the encryption key, must be overriden in each child class.
	string virtual getKey();
	//Encodes the message, virtual so that child classes can override it.
	string virtual encode(string message);
	//Decodes the message, virtual so that child classes can override it.
	string virtual decode(string message);

private:
	//Holds the morse code
	string code[36];

protected:
	//The name of the cipher.
	string name;

};