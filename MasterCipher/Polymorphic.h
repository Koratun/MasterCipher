#pragma once
#include "Caesar.h"
class Polymorphic : public Caesar
{
public:
	Polymorphic();
	Polymorphic(string key);
	//Returns a string form of the encryption key, must be overriden in each child class.
	string virtual getKey();
	//Encodes the message
	string virtual encode(string message);
	//Decodes the message
	string virtual decode(string message);

private:
	string key;
	bool decoding = false;
};

