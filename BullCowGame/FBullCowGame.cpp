#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset() {
	const FString HIDDEN_WORD = "planet"; //This must be an isogram (word with no repeating letters)
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
	bGameWon = false;

	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength && BullCowCount.Cows == 0) {
		bGameWon = true;
	}

	return BullCowCount;
}
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	} else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const {
	if (Word.length() <= 1) { return true; }
	
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; } 
		else { LetterSeen[Letter] = true; }
	}
	
	return true;
}
bool FBullCowGame::IsLowercase(FString Word) const {
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) {
		if (!islower(Letter)) { return false; }
	}

	return true;
}
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap <int32, int32> WordLengthToMaxTries{{ 3,4 },{ 4,7 },{ 5,10 },{ 6,15 },{ 7,20 }};
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }