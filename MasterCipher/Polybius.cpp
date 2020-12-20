#include "Polybius.h"
#include "functions.h"

#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

const string Polybius::LAYOUTS[5][6] = {
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

//The constant pointer string array is initialized to point at a string array object containing these five items.
string* const Polybius::layoutNames = new string[]{
	"Standard",
	"Backward",
	"Spiral",
	"Upside down",
	"Reverse"
};

Polybius::Polybius(int layout) :
	squareLayout(layout),
	Cipher("Polybius Square")
{}


Polybius::Polybius(string layoutName) :
	//This shorthand takes the layoutNames pointer of an array of strings and finds the address of the given layoutName, 
	//	then calculate using the distance algorithm how many address spaces away the given layoutName is from the first element in the pointer array. 
	//	This should give the Polybius class the integer it needs to determine which layout to use.
	squareLayout(distance(layoutNames, find(layoutNames, layoutNames + 5, layoutName))),
	Cipher("Polybius Square")
{}


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

string Polybius::getKey()
{
	return "the " + layoutNames[squareLayout] + " layout";
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
		if (isUpper(c))
		{
			toLower(c);
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
				encodedMessage += to_string(col + 1) + to_string(row + 1);
				return;
			}
		}
	}
	cout << "Unrecognized character: " << c << endl;
}

string Polybius::decode(string message)
{
	//Error handling. If a character other than a space or a number between 1-6 is entered, then an error is returned.
	for (char c : message)
	{
		if (!(c >= '1' && c <= '6') && c != ' ')
		{
			return "ERROR: INCOMPATIBLE MESSAGE FOR POLYBIUS SQUARE";
		}
	}

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
			cout << "Warning: An odd number of numbers was entered. This could have unpredictable results. Skipping current coordinate.\n";
			return decodedMessage;
		}

		//If there aren't enough coordinates before a space, a warning prints, a space is added to the message, it skips the current coordinate and it goes to the next loop.
		if (message[i + 1] == ' ')
		{
			cout << "Warning: An odd number of numbers was entered. This could have unpredictable results. Skipping current coordinate.\n";
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