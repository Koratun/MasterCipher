#include "Caesar.h"
#include "functions.h"

#include<iostream>
#include<string>

using namespace std;

//The base constructor for Caeser's Cipher.
Caesar::Caesar() :
	Cipher("Caesar's Cipher")
{
	cout << "\nYou have chosen " << name << "!\n";
	cout << "This cipher takes the alphabet and pairs them with numbers corresponding with their position in the alphabet.\n";
	cout << "For example, A=1, B=2, C=3, etc.\n\nThe cipher then takes a given number and adds that value to the value of the letters in the message and\ngives back the encoded message.\n\n";

	cout << "If you are decoding a message, please input the number used to create the cipher originally.\n";
	do
	{
		cout << "\nPlease enter a number.\n> ";
		cin >> translationAmount;
		cin.ignore();
		cout << "\nA=" << getCodedLetterValue('A');
	} while (!yesNoQuestion("\nIs this what you want?"));

}

//The constructor used to make a quick an easy cipher
Caesar::Caesar(int key) :
	translationAmount(key),
	Cipher("")
{}

//Constructor for child ciphers to call.
Caesar::Caesar(string name) :
	Cipher(name)
{}

string Caesar::getKey()
{
	return "A=" + to_string(translationAmount + 1) + " or A=" + getCodedLetterValue('A');
}

//Returns the encoded value of 'A'. Simply multiply translationAmount by -1 and run this method again to get the decoded value.
char Caesar::getCodedLetterValue(char letterValue)
{
	bool isLetter = (isUpper(letterValue)) || (isLower(letterValue));
	bool isNumber = letterValue >= '0' && letterValue <= '9';
	//If the character is not a letter or number, then do nothing to it.
	if (!isLetter && !isNumber)
	{
		return letterValue;
	}

	bool capital = isUpper(letterValue);
	for (int i = 0; i < abs(translationAmount); i++)
	{
		//Add one to the letter value if the amount is positive, subtract one if negative.
		if (translationAmount > 0)
		{
			letterValue++;
		}
		else
		{
			letterValue--;
		}

		//Roll around if value goes out of range.
		if (isNumber)
		{
			if (letterValue < '0')
			{
				letterValue = '9';
			}
			else if (letterValue > '9')
			{
				letterValue = '0';
			}
		}
		else
		{
			if (letterValue < (capital ? 'A' : 'a'))
			{
				letterValue = (capital ? 'Z' : 'z');
			}
			else if (letterValue > (capital ? 'Z' : 'z'))
			{
				letterValue = (capital ? 'A' : 'a');
			}
		}
	}
	return letterValue;
}

string Caesar::encode(string message)
{
	string encodedMessage = "";
	//Loop through each letter in the message and add its coded value to the encoded message.
	for (char c : message)
	{
		encodedMessage += getCodedLetterValue(c);
	}
	return encodedMessage;
}

string Caesar::decode(string message)
{
	//Simply reverse the encoding process to decode the message.
	translationAmount *= -1;
	string decodedMessage = encode(message);
	translationAmount *= -1;
	return decodedMessage;
}