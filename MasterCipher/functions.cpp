#include "functions.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

string stringQuestion(string question)
{
	cout << question;
	string s;
	getline(cin, s);
	return s;
}

int intQuestion(string question, int large, int small)
{
	int n;
	do
	{
		cout << question;
		cin >> n;
		//While the answer is not within the acceptable range, keep asking.
	} while (!(n >= small && n <= large));
	clearCinBuffer();
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
	clearCinBuffer();
	return c == 'Y' || c == 'y';
}

//Please use this after every cin request besides getline().
void clearCinBuffer()
{
	string trash;
	getline(cin, trash);
	return;
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