#include "functions.h"
#include "Cipher.h"
#include "Caesar.h"
#include "Polybius.h"
#include "Polymorphic.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

string stringQuestion(string question, string hintMessage)
{
	cout << question;
	string s;
	getline(cin, s);
	if (hintMessage != "" && s == "hint")
	{
		cout << "\nHint: " << hintMessage << endl;
		cout << question;
		getline(cin, s);
	}
	return s;
}

int intQuestion(string question, int large, int small, string hintMessage)
{
	int n;
	do
	{
		cout << question;
		if (hintMessage != "")
		{
			string s;
			cin >> s;
			if (s == "hint")
			{
				cout << "\nHint: " << hintMessage << endl;
				cout << question;
				cin >> n;
			}
			else
			{
				//If the user types something that cannot be turned into a number, this try catch block deals with it.
				try
				{
					n = stoi(s);
				}
				catch (invalid_argument e)
				{
					//If the user does not type 'hint' or a valid number, then 'n' is set to outside the acceptable number range and the program interprets this as the user inputting a wrong number.
					n = small - 1;
				}

			}
		}
		else
		{
			cin >> n;
		}
		//Clear anything in the buffer if necessary.
		cin.ignore();

		//While the answer is not within the acceptable range, keep asking.
	} while (!(n >= small && n <= large));
	return n;
}

bool yesNoQuestion(string question)
{
	cout << question;
	char c;
	do
	{
		cout << "\nY/N\n> ";
		cin >> c;
		//While not a yes or no answer, keep asking.
	} while (c != 'Y' && c != 'y' && c != 'N' && c != 'n');
	cin.clear();
	return c == 'Y' || c == 'y';
}

bool isUpper(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool isLower(char c)
{
	return c >= 'a' && c <= 'z';
}

bool isLetter(char c)
{
	return isUpper(c) || isLower(c);
}

void toLower(char& c)
{
	c = c - 'A' + 'a';
}

vector<string> splitString(string toSplit, string delimiter)
{
	vector<string> words;
	int position = toSplit.find(delimiter);
	//If there is no delimiter present, then add the whole string and exit the function.
	if (position == string::npos)
	{
		words.push_back(toSplit);
		return words;
	}

	//While more of the delimiter is in the remainder of the string, add the string from the beginning of the string to the delimiter.
	while ((position = toSplit.find(delimiter)) != string::npos)
	{
		//Even though 'words' was initially created as a pointer to an array, C++ cannot tell the difference between this and a normal array, so array notation is allowed.
		words.push_back(toSplit.substr(0, position));
		//Delete the portion of the string just added plus the delimiter.
		toSplit.erase(0, position + delimiter.size());
	}
	words.push_back(toSplit);
	return words;
}

Cipher* createCipher(int which)
{
	switch (which)
	{
	case 1:
		return new Caesar();
	case 2:
		return new Polybius();
	case 3:
		return new Cipher();
	case 4:
		return new Polymorphic();
	}
}

void listCiphers()
{
	cout << "1. Caesar's cipher; Uses the numeric values of the alphabet to alter the message.\n";
	cout << "2. Polybius Square; Uses a grid to encode characters based on coordinates.\n";
	cout << "3. Morse Code; Uses dots and dashes to represent certain characters.\n\tCan be used to communicate when only two states are communicable.\n";
	cout << "4. Polymorphic cipher; Similar to Caesar's cipher, but uses a keyword\n\tto generate different encryption values for each character in the message.\n";
}

void playLevelLoop(string answer, string encryptedMessage, string hint)
{
	//Create variables needed to be out of the scope of the loop.
	//Initialize cipher pointer to address zero. Effectively null. Sort of.
	Cipher* guessCipher = 0;
	//The string to hold the attempted decryption of the message.
	string attempt;

	do
	{
		guessCipher = createCipher(intQuestion("\n> ", 4, 1, hint));

		cout << "\nWith the " << guessCipher->getName() << " and the encryption key of " + guessCipher->getKey() + ", the message reads...\n\n";

		attempt = guessCipher->decode(encryptedMessage);
		cout << attempt << "\n\n";

		if (attempt != answer)
		{
			cout << "Hmm, that doesn't make any sense. That can't be the right encryption key.\nTry again.\n";
			cout << "What cipher do you think it is?\n";
			listCiphers();
		}

	} while (attempt != answer);
}