/*
Kody Mitchell
12/01/2020
Final Project - A program meant to show off all our shiny new C++ skills!
Master Cipher V2.0 - A program that takes user input to encode or decode a message with one or multiple ciphers.
*/

#include "functions.h"
#include "Cipher.h"
#include "Caesar.h"
#include "Polybius.h"
#include "Polymorphic.h"

#include<iostream>
#include<string>
#include<vector>

using namespace std;

//Note: The internal code for the Polybius class uses a reference.

int main()
{
	cout << "Welcome to the Master Cipher Program.\n";
	string username = stringQuestion("What is your name? ");

	cout << "Hello " << username << "! This program can encode or decode any message you give it.\n\nSimply select encode or decode first and then select which cipher you want to use.\n";
	cout << "Most ciphers require additional setup and you will be directed how to do so with each cipher.\n\n";

	do
	{
		cout << "This program has an adventure mode and a creative mode.\nIt is recommended that you play around in creative mode a bit to teach yourself about the\nvarious ciphers this program is capable of using before you enter adventure mode.\n";

		if (yesNoQuestion("\nDo you want to play adventure mode?"))
		{
			//Level 1
			//Create the cipher that the user must create in order to pass the level.
			Cipher* correctCipher = new Caesar(7-13);

			//Create the decrypted message
			string answer = "Caesar's cipher is too easy to break, we need to strengthen our encryption.\nDecode next message with the most legendary of ancient beasts.";

			//Encrypt the message with this level's cipher.
			string encryptedMessage = correctCipher->encode(answer);

			cout << "\n\nWelcome Special Agent " << username << ". We are glad you could arrive on such short notice.\n";
			cout << "We've intercepted an encrypted message from an unknown source on one of\n\tour channels but our cryptographers are unable to crack it.\n";
			cout << "We've called for your help so we can learn what this message means.\n\nOur cyber analysts were able to recover one additional piece of information with the transmission:\n'13=7'\n\nWe are unsure what this means and we need your help.\n";
			cout << "The original message reads:\n" << encryptedMessage << endl;

			cout << "\nWhich cipher do you think it is? (type 'hint' here for one hint per level)\n";
			listCiphers();

			playLevelLoop(answer, encryptedMessage, "A=1");

			cout << "That's it! Brilliant job Agent " << username << "!\n\n";

			//Level 2
			cout << "\t\tTWO WEEKS LATER\n\n";
			cout << "Special Agent " << username << ", we could use your help again.\n";

			correctCipher = new Polymorphic("dragon");

			answer = "The feds are catching onto us, we need to change our strategy entirely.\nUse the mirror image to decode the next message.";

			encryptedMessage = correctCipher->encode(answer);

			//Causes program to wait until the user presses enter.
			cin.ignore();

			cout << "We've received another troubling message that has our guys baffled.\nThe unknown actors weren't as messy this time and they didn't leave anything for our cyber analysts to find.\n\n";
			
			cout << "The original message reads:\n" << encryptedMessage << endl;

			cout << "\nGood luck Agent " << username << ".\n";

			cout << "\nWhich cipher do you think it is? (type 'hint' here for one hint per level)\n";
			listCiphers();

			playLevelLoop(answer, encryptedMessage, "A fire-breathing creature");

			cout << "Outstanding work Agent " << username << "!\nWe couldn't have done it without you!\n\n";

			//Final level
			cout << "\t\tTHE NEXT DAY\n\n";

			correctCipher = new Polybius("Reverse");

			answer = "yeah i will have a number 2 no just the sandwich please thank you";

			encryptedMessage = correctCipher->encode(answer);

			cin.ignore();
			cout << "Agent " << username << "!\nI'm glad I caught you! One of our men on the inside was able to transmit an internal encrypted message to us.\n";
			cout << "This one has us completely confused. We need you to put your skills to the test to solve this one!\n\n";
			cout << "Here's the encrypted message:\n" << encryptedMessage << endl;
			cout << "\nGood luck Agent " << username << ".\n";

			cout << "\nWhich cipher do you think it is? (type 'hint' here for one hint per level)\n";
			listCiphers();

			playLevelLoop(answer, encryptedMessage, "What effect do mirrors have on images?");

			cout << "Oh, well. That's awkward. Our guy was sure this was important. Sorry to waste your time Agent " << username << ".\nThank you for your help!\n\n";

			cout << "\t\tGAME COMPLETE!\n\n";
		}
		else
		{
			//If true, then we are encoding, if false, then decoding.
			bool encode = intQuestion("\nDo you want to \n1. Encode or\n2. Decode?\n> ", 2) == 1;

			cout << "\nPlease type the message you want to " << (encode ? "en" : "de") << "code.\n";

			string message = stringQuestion("> ");

			cout << "\nHere are the currently available ciphers:\n";
			listCiphers();

			//Initialize cipher to a pointer of the appropriate cipher created by the createCipher function.
			Cipher* cipher = createCipher(intQuestion("\nPlease type the number of which cipher you want to use.\n> ", 4));

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
		}

	} while (yesNoQuestion("\nDo you want to run this program again?"));

	cout << "\n\nGoodbye " << username << "!\n";

	return 0;
}