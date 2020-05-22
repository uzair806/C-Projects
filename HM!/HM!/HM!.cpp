// HM!.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <iostream>
#include <string>

using namespace std;

string board = "|---| \n|     \n|     \n|     \n|     \n------"; //Initial boardb before incorrect guesses are given
string bank = " "; //Initial bank before guesses are given
void makeboard(int errors); //Function headers
bool verifier(string word);
string blankmaker(string word);
bool bankcheck(char guess);
void displaybank();
string blankfiller(char letter, string blanks, string word);
int main() {
	int errors = 0, guesses = 6;
	char guess;
	string blanks, word;
	
	cout << "Welcome to Hangman, please choose a word (no numbers): ";
	cin >> word;
	while (verifier(word) == false) { //Validation from the verfier function to check if there is a number within the word
		cout << "remember, no numbers, please enter another word: ";
		cin >> word;
	}
	blanks = blankmaker(word); //Converts word to blanks
	while (errors < 6) { //Loops through program until player guesses incorrectly too many times
		system("cls");
		cout << board << "\n\n " << blanks << "\n\nYou have " << guesses << " guesses left" << "\nThe word is " << word.length() << " letter(s) long (including spaces and hyphens" <<"\n\nYou've currently used:";
		displaybank(); 
		cout << "\n\nPlease guess a letter: "; //These last three lines are there for displaying the players info
		cin >> guess; //Player adds a guess
		while (!isalpha(guess)) { //Validation check for a letter guess
			cout << "\n\nThat is not a letter, please guess another letter: ";
			cin >> guess;
		}

		while (!bankcheck(guess)) { //Validates to see if the player already chose this letter before
			cout << "\n\nYou've already used that letter, please guess another letter: ";
			cin >> guess;
		}
		
		if (blankfiller(guess, blanks, word) == "0") { //checks if the guess is wrong then adjusts the board
			errors++;
			guesses--;
			makeboard(errors);
		}
		else
			blanks = blankfiller(guess, blanks, word); //if letter is in the word, populates the blank with the letter in its place

		if (blanks == word) { //Win if blanks and word match. meaning all the letter were guessed correctly before guesses ran out
			system("cls");
			cout << "The Word is: " << blanks << "!\nYou win!";
			errors = 7;
		}
	}
	if (blanks != word) {//Lose if while loop ends with guesses equalling 0. Meaning that the guesses have ran out
		system("cls");
		cout << board << "\nYou lose\n The word was: " << word;
	}
	cin.get();
};

void displaybank() { //Displays all the letters the player has used before
	for (int i = 0; i < bank.length(); i++) {
		cout << bank[i];
	}
}

bool bankcheck(char guess) { //checks bank to see if the letter has been used
	for (int i = 0; i < bank.length(); i++) {
		if (bank[i] == guess) {
			return false;
		}
	}
	bank += guess; 
	bank += ", "; //Formats bank so it looks nicer when printed out
	return true;
}

string blankfiller(char letter, string blanks, string word) { //Fills in the blanks with part of the word that were guessed correctly
	int check = 0;
	for (int i = 0; i < blanks.length(); i++) {
		if (tolower(word[i]) == tolower(letter)) {
				blanks[i] = word[i];
			check++;
		}
	}
	if (check > 0) {
		return blanks;
	}
	else 
		return "0";
}

string blankmaker(string word) { //Converts the word to blanks and puts in as many blanks, hypens ot spaces necessary
	string blanks = "";
	for (int i = 0; i < word.length(); i++) {
		if (word[i] == '-') {
			blanks += '-';
		}

		else if (word[i] == ' ') {
			blanks += ' ';
		}
		else
			blanks += "_";
	}
	return blanks;
}

bool verifier(string word) { //Verifies that each space is a letter
	for (int i = 0; i < word.length(); i++) {
		if (isdigit(word[i])) {
			return false;
		}
	}

	return true;
}
void makeboard(int errors) { //Populates the board with the hangman pieces when an incorrect input is given
	if (errors == 1) {
		board[11] = 'O';
	}
	else if (errors == 2) {
		board[18] = '|';
	}
	else if (errors == 3) {
		board[17] = '/';
	}
	else if (errors == 4) {
		board[19] = '\\';
	}
	else if (errors == 5) {
		board[24] = '/';
	}
	else if (errors == 6) {
		board[26] = '\\';
	}
}
