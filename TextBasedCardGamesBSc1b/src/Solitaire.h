#pragma once
#include "Deck.h"
#include "Random.h"
#include "Input.h"

class Solitaire
{
public:
	//Plays the game
	static void PlayGame();
	//Combines the card strings so that they are on the same line
	static std::wstring CombineCardsAsString(const std::wstring& card1, const std::wstring& card2);
	//Returns a string representation of a deck face up
	static std::wstring LayoutDeckAsString(Deck& deck);
	//Returns a string representation of two strings printed out next to each other (first line of the second string will be appended to the first line of the first string etc.)
	static std::wstring AppendStringsOnSamePrintLine(const std::wstring& string1, const std::wstring& string2);
	//Returns whether or not the piles has a valid pair
	static bool HasAValidPair(std::vector<Card>& piles);
};