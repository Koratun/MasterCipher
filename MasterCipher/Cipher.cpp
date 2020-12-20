#include "Cipher.h"
#include "functions.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

//A constructor to save the name of this Cipher and for all child ciphers to call.
Cipher::Cipher(string name) :
	name(name)
{}

//Base constructor for the Morse Code cipher.
Cipher::Cipher() :
	Cipher("Morse Code")
{
	cout << "\n\nYou have chosen " << name << "!\n";
	cout << "This cipher requires no additional setup. Note that it cannot handle special characters.\nIf you are decoding Morse, please separate letters with one space ' ' and words with two spaces '  '.\n\n";

	int i = 0;
	//Letters A-Z, index starts at 0
	code[i++] = ".-";
	code[i++] = "-...";
	code[i++] = "-.-.";
	code[i++] = "-..";
	code[i++] = ".";
	code[i++] = "..-.";
	code[i++] = "--.";
	code[i++] = "....";
	code[i++] = "..";
	code[i++] = ".---";
	code[i++] = "-.-";
	code[i++] = ".-..";
	code[i++] = "--";
	code[i++] = "-.";
	code[i++] = "---";
	code[i++] = ".--.";
	code[i++] = "--.-";
	code[i++] = ".-.";
	code[i++] = "...";
	code[i++] = "-";
	code[i++] = "..-";
	code[i++] = "...-";
	code[i++] = ".--";
	code[i++] = "-..-";
	code[i++] = "-.--";
	code[i++] = "--..";

	//Numbers 0-9, index starts at 26
	code[i++] = "-----";
	code[i++] = ".----";
	code[i++] = "..---";
	code[i++] = "...--";
	code[i++] = "....-";
	code[i++] = ".....";
	code[i++] = "-....";
	code[i++] = "--...";
	code[i++] = "---..";
	code[i] = "----.";

}

string Cipher::getName()
{
	return name;
}

string Cipher::getKey()
{
	return "morse code";
}

string Cipher::encode(string message)
{
	string encodedMessage = "";
	for (char c : message)
	{
		//If the character is a space, then add a newline character and move to the next loop.
		if (c == ' ')
		{
			encodedMessage += '\n';
			continue;
		}

		//If the letter is capitalized, then make it lowercase.
		if (isUpper(c))
		{
			c = c - 'A' + 'a';
		}

		//If it is a number, read from the number section of the morse code chart.
		if (c >= '0' && c <= '9')
		{
			encodedMessage += code[c - '0' + 26] + ' ';
		}
		//Otherwise read from the letter section of the chart.
		else if (isLower(c))
		{
			encodedMessage += code[c - 'a'] + ' ';
		}
		//If the character cannot be encoded, then print an error.
		else
		{
			cout << "Unrecognized character: " << c << endl;
		}
	}
	return encodedMessage;
}

string Cipher::decode(string message)
{
	string decodedMessage = "";

	vector<string> words = splitString(message, "  ");

	//Loops through each element of words and decodes each letter.
	for (int i = 0; i < words.size(); i++)
	{
		int position;
		while ((position = words[i].find(" ")) != string::npos)
		{
			//Take the next sequence of morse code symbols representing a letter.
			string letter = words[i].substr(0, position);
			//Get the index of the letter sequence that matches the morse code.
			for (int x = 0; x < 36; x++)
			{
				if (code[x] == letter)
				{
					//If it's a number just subtract 26 and convert the number to a string.
					if (x > 25)
					{
						decodedMessage += (x - 26);
					}
					//If it's a letter, convert the index to an ASCII value.
					else
					{
						char c = x + 'a';
						decodedMessage += c;
					}
					break;
				}
				if (x == 35)
				{
					cout << "Unrecognized morse code: " << letter << endl;
				}
			}
			words[i].erase(0, position + 1);
		}

		//Get the index of the letter sequence that matches the morse code.
		for (int x = 0; x < 36; x++)
		{
			//What is left in words[i] is the last letter, no need to store it in another variable.
			if (code[x] == words[i])
			{
				//If it's a number just subtract 26 and convert the number to a string.
				if (x > 25)
				{
					decodedMessage += (x - 26);
				}
				//If it's a letter, convert the index to an ASCII value.
				else
				{
					char c = x + 'a';
					decodedMessage += c;
				}
				break;
			}
			if (x == 35)
			{
				cout << "Unrecognized morse code: " << words[i] << endl;
			}
		}

		//Add a space before we go to the next word.
		decodedMessage += ' ';

	}

	return decodedMessage;
}