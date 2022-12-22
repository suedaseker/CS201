#include <iostream>
#include <string>
#include "strutils.h"
using namespace std;

string GetInput(string &word, string &name1, string &name2)
{
	cout << name1 << ", please input the word you want "<< name2 << " to guess: ";
	cin >> word;
	word = LowerString(word);
	return word;
}

bool InputCheck(string word)
{
	char i;
	bool condition;
	for (int k = 0,length = word.length(); k < length; k++)
	{
		i = word[k];
		if (i >= 'a' && i <= 'z'){
			condition = true;
		}else{
			condition = false;
			break;
		}
	}
	return condition;
}

string GetOption(string &option, string &name2, string &unknown)
{
	cout << "The word is: " << unknown << endl;
	cout << name2 << ", do you want to guess the word(1) or guess a letter(2)? ";
	cin >> option;
	return option;
}

bool OptionCheck(string option)
{
	if (option == "1" || option == "2"){
		return true;
	}else{
		return false;
	}
}

string GetGuess(string &option, string &guess1, string &guess2)
{
	if (option == "1"){
		cout << "Your guess: ";
		cin >> guess1;
		guess1 = LowerString(guess1);
		return guess1;

	}else{
		cout << "Your guess: ";
		cin >> guess2;
		guess2 = LowerString(guess2);
		return guess2;
	}
}

bool GuessCheck(string option, string guess1, string guess2)
{
	bool condition;
	if (option == "1")
	{
		char i;
		for (int k = 0,length = guess1.length(); k < length; k++)
		{
			i = guess1[k];
			if (i >= 'a' && i <= 'z'){
				condition = true;
			}else{
				condition = false;
				break;
			}
		}

	}else{
		if (guess2.length() == 1){
			if (guess2[0] >= 'a' && guess2[0] <= 'z'){
				condition = true;
			}else{
				condition = false;
			}
		}else{
			condition = false;	
		}
	}
	return condition;
}

bool IsEntered(string option, string guess1, string guess2, string &entered1, string &entered2)
{
	if (option == "1"){
		if (entered1.find(guess1) != string::npos)
		{
			return false;

		}else{
			entered1 = entered1 + guess1;
			return true;
		}
	}else{
		if (entered2.find(guess2) != string::npos)
		{
			return false;
		}else{
			entered2 = entered2 + guess2;
			return true;
		}
	}
}

string FoundLetters(string &word, string &guess2, string &unknown)
{

	for (int k = 0, length = word.length(); k < length; k++)
	{
		if (word[k] == guess2[0]){
			unknown[k] = word[k];
		}
		else{
			unknown = unknown;
		}
	}
	return unknown;
}

string ValidGuess(string &option, string &guess1, string &guess2, string &unknown, string &name2)
{
	GetOption(option, name2, unknown);
	while (OptionCheck(option) == false)
	{
		cout << "Invalid option!" << endl; 
		GetOption(option, name2, unknown);
	}

	GetGuess(option, guess1, guess2);
	while (GuessCheck(option, guess1, guess2) == false) 
	{
		cout << "Invalid entry! Try again." << endl;
		GetOption(option, name2, unknown);

		while (OptionCheck(option) == false)
		{
			cout << "Invalid option!" << endl; 
			GetOption(option, name2, unknown);
		}
		GetGuess(option, guess1, guess2);
	}
	if (option == "1"){
		return guess1;
	}else{
		return guess2;
	}
}


int main()
{
	cout << "Welcome to the HANGMAN GAME" << endl << "---------------------------" << endl;
	string name1, name2;
	cout << "Player one, please enter your name: ";
	cin >> name1;
	cout << "Player two, please enter your name: ";
	cin >> name2;
	cout << "OK " << name1 << " and " << name2 << ". Let's start the game!" << endl;

	string word;
	GetInput(word, name1, name2);
	while ((InputCheck(word) == false))
	{
		cout << "Invalid word! Try again." << endl;
		GetInput(word, name1, name2);
	}
	string unknown;
	for (int k = 0,length = word.length(); k < length; k++)
	{
		unknown = unknown + "-";
	}
	cout << name2 << ", you have 1 free guess, after that you will lose limbs!" << endl;

	int wrong = 0;
	bool run = true;
	
	string entered1 , entered2;

	while (true)
	{	
		string option;
		string guess1, guess2;
		ValidGuess(option, guess1, guess2, unknown, name2);

		while (IsEntered(option, guess1, guess2, entered1, entered2) == false)
		{
			cout << "Guess entered before! Try again." << endl;
			ValidGuess(option, guess1, guess2, unknown, name2);	
		}

		if (option == "1"){
			if (guess1 == word){
			cout << "The word is: " << word << endl;
			cout << "Congratulations " << name2 << ", you won!" << endl;
			cout << name2 << " won the game!";
			break;
			}
		}else{
			FoundLetters(word, guess2, unknown);
			if (unknown == word){
				cout << "The word is: " << word << endl;
				cout << "Congratulations " << name2 << ", you won!" << endl;
				cout << name2 << " won the game!";
				break;			
			}
		}

		if (option == "2" && word.find(guess2) != string::npos){
			FoundLetters(word, guess2, unknown);
		}else{	
			if (wrong == 0){
				cout << "You have no free guess left." << endl;
				wrong ++;
			}else if (wrong == 1 || wrong == 2){
				cout << "You have lost a leg!" << endl; 
				wrong ++;
			}else if (wrong == 3 || wrong == 4){
				cout << "You have lost an arm!" << endl;
				wrong ++;
			}else if (wrong == 5){
				cout << "You have lost a head! GAME OVER!" << endl;
				cout << name2 << " lost the game :(";
				break;
			}
		}
	}
	return 0;
}
