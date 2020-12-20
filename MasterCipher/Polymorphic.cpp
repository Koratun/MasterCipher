#include "Polymorphic.h"
#include "Cipher.h"
#include "functions.h"

#include<iostream>
#include<string>

using namespace std;

Polymorphic::Polymorphic() :
	Caesar("Polymorphic Cipher")
{
	cout << "\nYou have chosen the " << name << "!\n\n";
	cout << "Much like the Caesar cipher, this converts letters of the alphabet to numbers.\n";
	cout << "However the amount of characters to shift over is not the same every time.\n\n";
	cout << "A keyword is given and the number values from each of these letters is used to encrypt or decrypt the message.\n";
	cout << "When the end of the keyword is reached, the cipher simply moves back to the start of the word.\n\n";

	key = stringQuestion("What is your keyword? ");

	//Errorproof the given keyword. Delete anything that isn't a letter and make all the characters lowercase.
	for (int i = 0; i < key.size(); i++)
	{
		if (!isLetter(key[i]))
		{
			//Delete any characters that are not letters.
			key.erase(i--, 1);
			continue;
		}

		//If the character is uppercase, then make it lowercase.
		if (isUpper(key[i]))
		{
			toLower(key[i]);
		}
	}
}

Polymorphic::Polymorphic(string key) :
	key(key),
	Caesar("Polymorphic Cipher")
{}

string Polymorphic::getKey()
{
	return key;
}

string Polymorphic::encode(string message)
{

	string encodedMessage = "";
	unsigned int i = 0;
	//Loop through each letter in the message and add its coded value to the encoded message.
	for (char c : message)
	{
		//Change the translation amount that the Caesar cipher will use to encode (or decode) the message.
		translationAmount = (key[i++] - 'a' + 1) * (decoding? -1 : 1);
		//If i is out of the index range of the keyword, then this calculation will return i to 0.
		i %= key.size();
		//Employ the Caesar cipher on this char.
		encodedMessage += Caesar::getCodedLetterValue(c);
	}
	return encodedMessage;
}

string Polymorphic::decode(string message)
{
	//Just perform the encoding algorithm with negative translation values.
	decoding = true;
	string decodedMessage = encode(message);
	decoding = false;
	return decodedMessage;
}