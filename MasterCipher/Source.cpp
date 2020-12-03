/*
Kody Mitchell
12/01/2020
Header and Source files - A program meant to teach us how to use header and other source files.
Master Cipher V1.0 - A program that takes user input to encode or decode a message with one or multiple ciphers.
*/

#include "functions.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;


//Class declarations

//A Base cipher class that all other ciphers will be derived from. This is also the Morse Code cipher class.
class Cipher
{
public:
	Cipher();
	Cipher(string name);
	//The name of the cipher.
	string name;
	//Encodes the message, virtual so that child classes can override it.
	string virtual encode(string message);
	//Decodes the message, virtual so that child classes can override it.
	string virtual decode(string message);

private:
	//Holds the morse code
	string code[36];
};

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
		if (c >= 'A' && c <= 'Z')
		{
			c = c - 'A' + 'a';
		}

		//If it is a number, read from the number section of the morse code chart.
		if (c >= '0' && c <= '9')
		{
			encodedMessage += code[c - '0' + 26] + ' ';
		}
		//Otherwise read from the letter section of the chart.
		else if(c >= 'a' && c <= 'z')
		{
			encodedMessage += code[c - 'a'] + ' ';
		}
		//If the character cannot be encoded, then print an error.
		else
		{
			cout << "\nUnrecognized character: " << c;
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
					cout << "\nUnrecognized morse code: " << letter;
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
				cout << "\nUnrecognized morse code: " << words[i];
			}
		}

		//Add a space before we go to the next word.
		decodedMessage += ' ';

	}

	return decodedMessage;
}

//A constructor to save the name of this Cipher
Cipher::Cipher(string name) :
	name(name)
{}



//The Caeser's Cipher class
class Caeser : public Cipher
{
public:
	Caeser();
	//Encodes the message
	string virtual encode(string message);
	//Decodes the message
	string virtual decode(string message);

private:
	//The amount to translate the message through the alphabet.
	int translationAmount;
	//Returns the encoded value of the given letter value where A=1. Simply multiply translationAmount by -1 and run this method again to get the decoded value.
	char getCodedLetterValue(char letterValue);
};

//The base constructor for Caeser's Cipher.
Caeser::Caeser() :
	Cipher("Caeser's Cipher")
{
	cout << "\nYou have chosen " << name << "!\n";
	cout << "This cipher takes the alphabet and pairs them with numbers corresponding with their position in the alphabet.\n";
	cout << "For example, A=1, B=2, C=3, etc.\n\nThe cipher then takes a given number and adds that value to the value of the letters in the message and\ngives back the encoded message.\n\n";

	cout << "If you are decoding a message, please input the number used to create the cipher originally.\n";
	do
	{
		cout << "\nPlease enter a number.\n> ";
		cin >> translationAmount;
		cout << "\nA=" << getCodedLetterValue('A');
	} while (!yesNoQuestion("\nIs this what you want?"));

}

//Returns the encoded value of 'A'. Simply multiply translationAmount by -1 and run this method again to get the decoded value.
char Caeser::getCodedLetterValue(char letterValue)
{
	bool isLetter = (letterValue >= 'A' && letterValue <= 'Z') || (letterValue >= 'a' && letterValue <= 'z');
	bool isNumber = letterValue >= '0' && letterValue <= '9';
	//If the character is not a letter or number, then do nothing to it.
	if (!isLetter && !isNumber)
	{
		return letterValue;
	}

	bool capital = letterValue >= 'A' && letterValue <= 'Z';
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

string Caeser::encode(string message)
{
	string encodedMessage = "";
	//Loop through each letter in the message and add its coded value to the encoded message.
	for (char c : message)
	{
		encodedMessage += Caeser::getCodedLetterValue(c);
	}
	return encodedMessage;
}

string Caeser::decode(string message)
{
	//Simply reverse the encoding process to decode the message.
	translationAmount *= -1;
	string decodedMessage = Caeser::encode(message);
	translationAmount *= -1;
	return decodedMessage;
}


//The Polybius Square class
class Polybius : public Cipher
{
public:
	Polybius();
	//Encodes the message
	string virtual encode(string message);
	//Decodes the message
	string virtual decode(string message);

private:
	//Lets you know which layout is selected.
	int squareLayout;

	//A static member of this class that holds all the premade layouts for the Polybius Square.
	const string LAYOUTS[5][6] = {
		{ //Standard: 0
			"abcdef",
			"ghijkl",
			"mnopqr",
			"stuvwx",
			"yz0123",
			"456789"
		},
		{ //Backward: 1
			"987654",
			"3210zy",
			"xwvuts",
			"rqponm",
			"lkjihg",
			"fedcba"
		},
		{ //Spiral: 2
			"abcdef",
			"tuvwxg",
			"s567yh",
			"r498zi",
			"q3210j",
			"ponmlk"
		},
		{ //Upside Down: 3
			"456789",
			"yz0123",
			"stuvwx",
			"mnopqr",
			"ghijkl",
			"abcdef"
		},
		{ //Reverse: 4
			"fedcba",
			"lkjihg",
			"rqponm",
			"xwvuts",
			"3210zy",
			"987654"
		}
	};

	//Displays the Polybius square of the given layout.
	void displayGrid(int layout);
	//Adds the coordinates of the char in the Polybius square to the encoded message variable.
	void addCoordinates(char c, string& encodedMessage);

};

Polybius::Polybius() :
	Cipher("Polybius Square")
{
	cout << "\nYou have chosen the " << name << "!\n";
	cout << "\nThis cipher puts letters and numbers into a 6x6 grid and translates the input into the\ngrid coordinates that contain the appropriate character.\n";

	cout << "\nYou are now in demonstration mode. Select a layout to see what it looks like.";

	cout << "\n\nAvailable Polybius Square layouts:\n";
	cout << "1. Standard\n2. Backward\n3. Spiral\n4. Upside Down\n5. Reverse\n\n6. Enter selection mode";
	do
	{
		int choice = intQuestion("\n> ", 6);
		//If the user chose 6, then leave the loop.
		if (choice == 6)
			break;
		displayGrid(choice - 1);
	} while (true);

	cout << "\nYou are now in selection mode. Select a layout to encode or decode your message with.";
	cout << "\n1. Standard\n2. Backward\n3. Spiral\n4. Upside Down\n5. Reverse";

	squareLayout = intQuestion("\n> ", 5) - 1;

}

//Displays the Polybius square of the given layout.
void Polybius::displayGrid(int layout)
{
	cout << "\n    1   2   3   4   5   6";
	for (int row = 0; row < 13; row++)
	{
		//If it's an even row, display the edges of the board.
		if (row % 2 == 0)
		{
			cout << "\n  +---+---+---+---+---+---+";
		}
		else
		{
			//If it's an odd row, display which row it is (according to the polybius square).
			cout << endl << (int)(row / 2) + 1 << ' ';
			for (int col = 0; col < 25; col++)
			{
				//If the column is a multiple of 4, then print the edge of the board.
				if (col % 4 == 0)
				{
					cout << '|';
				}
				//If the column is 2 less than a multiple of 4, then print the corresponding character in the polybius square.
				else if (col % 4 == 2)
				{
					cout << LAYOUTS[layout][(int)(row / 2)][(int)(col / 4)];
				}
				//Otherwise print empty space.
				else
				{
					cout << ' ';
				}
			}
		}
	}
}

string Polybius::encode(string message)
{
	string encodedMessage = "";
	//Loop through every character in the message.
	for (char c : message)
	{
		//If it's a space, add the space and skip to the next loop.
		if (c == ' ')
		{
			encodedMessage += c;
			continue;
		}
		//Make the character lowercase if necessary. 
		if (c >= 'A' && c <= 'Z')
		{
			c = c - 'A' + 'a';
		}
		//Add the coordinates to the encoded message.
		Polybius::addCoordinates(c, encodedMessage);
	}
	return encodedMessage;
}

void Polybius::addCoordinates(char c, string& encodedMessage)
{
	//Loop through the polybius square until a match is found for the given character.
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 6; col++)
		{
			//When a match is found, add its column and row to the encoded message as literals.
			if (LAYOUTS[squareLayout][row][col] == c)
			{
				encodedMessage += to_string(col+1) + to_string(row+1);
				return;
			}
		}
	}
	cout << "\nUnrecognized character: " << c;
}

string Polybius::decode(string message)
{
	string decodedMessage = "";

	for (int i = 0; i < message.size(); i++) 
	{
		//If a space is seen, then add the space to the message and go to the next loop.
		if (message[i] == ' ')
		{
			decodedMessage += ' ';
			continue;
		}

		//If there aren't enough coordinates in the message, a warning prints and what has been decoded already is returned.
		if (i + 1 == message.size())
		{
			cout << "\nWarning: An odd number of numbers was entered. This could have unpredictable results. Skipping current coordinate.";
			return decodedMessage;
		}

		//If there aren't enough coordinates before a space, a warning prints, a space is added to the message, it skips the current coordinate and it goes to the next loop.
		if (message[i + 1] == ' ')
		{
			cout << "\nWarning: An odd number of numbers was entered. This could have unpredictable results. Skipping current coordinate.";
			decodedMessage += ' ';
			i++;
			continue;
		}
		//Get the letter at the coordinates specified by the next two numbers in the message.
		decodedMessage += LAYOUTS[squareLayout][message[i + 1] - '1'][message[i] - '1'];
		i++;
	}

	return decodedMessage;
}



//MAIN

int main()
{
	cout << "Welcome to the Master Cipher Program.\n";
	string username = stringQuestion("What is your name? ");

	cout << "Hello " << username << "! This program can encode or decode any message you give it.\nSimply select encode or decode first and then select which cipher you want to use.\n";
	cout << "Most ciphers require additional setup and you will be directed how to do so with each cipher.\n";

	do
	{
		//If true, then we are encoding, if false, then decoding.
		bool encode = intQuestion("\nDo you want to \n1. Encode or\n2. Decode?\n> ", 2) == 1;

		cout << "\nPlease type the message you want to " << (encode ? "en" : "de") << "code.\n";

		string message = stringQuestion("> ");

		cout << "\nHere are the currently available ciphers:\n";
		cout << "1. Caesar's cipher\n2. Polybius Square\n3. Morse Code\n";

		int response = intQuestion("\nPlease type the number of which cipher you want to use.\n> ", 3);

		//Cipher must be initialized here otherwise the compiler is unhappy.
		Cipher* cipher = new Cipher("dud");

		//Initialize the appropriate cipher and return its address with the 'new' command.
		switch (response)
		{
		case 1:
			cipher = new Caeser();
			break;
		case 2:
			cipher = new Polybius();
			break;
		case 3:
			cipher = new Cipher();
			break;
		}

		cout << "\n\nMessage: \n" << message << "\n\n" << (encode ? "En" : "De") << "coded:\n";
		//Encode or decode the message using the cipher.
		if (encode)
		{
			cout << cipher->encode(message) << endl;
		}
		else
		{
			cout << cipher->decode(message) << endl;
		}

		cout << "\nCipher complete!";

	} while (yesNoQuestion("\nDo you want to run this program again?"));

	cout << "\n\nGoodbye " << username << "!\n";

	return 0;
}