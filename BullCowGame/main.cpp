/* 
This is the console executable, that makes use of BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//Define Functions
void PrintIntro();
FText GetValidGuess();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();

//Instantiate Game
FBullCowGame BCGame; 

//Application Entry Point
int main() {
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	

	return 0; //Exit the Application
}

//Function to Introduce the Game
void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";

	return;
}

//Function to Start the Guessing
void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
}

//Function to Get Guess from the Player
FText GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	int32 CurrentTry = BCGame.GetCurrentTry();
	int32 MaxTries = BCGame.GetMaxTries();
	
	do {
		std::cout << "(Try " << CurrentTry << " of " << MaxTries << ") " << "Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n\n";
				break;
			default:
				break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "You won!\n";
	}
	else {
		std::cout << "YOu are out of guesses. Better luck next time...\n";
	}
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	getline(std::cin, Response);

	std::cout << "\n\n";

	return (Response[0] == 'y' || Response[0] == 'Y');
}