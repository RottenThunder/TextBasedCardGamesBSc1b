#pragma once
#include "Deck.h"
#include "Random.h"
#include "Input.h"

class Blackjack
{
public:
	//Plays the game
	static void PlayGame();
	//Gets the minimum value of a deck, counting all aces as 1
	static uint32_t GetMinValueOfHand(Deck& deck);
	//Gets the maximum value of a deck while trying to keep the value under 21
	static uint32_t GetMaxValueOfHand(Deck& deck);
	//Processes an AI's Turn and returns whether they have gone bust
	static bool TakeAITurn(const std::wstring& AIName, Deck& deck, Deck& mainDeck);
	//Returns a string representation of two strings printed out next to each other (first line of the second string will be appended to the first line of the first string etc.)
	static std::wstring AppendStringsOnSamePrintLine(const std::wstring& string1, const std::wstring& string2);
};