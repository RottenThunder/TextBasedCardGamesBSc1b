#pragma once
#include "Deck.h"
#include "Random.h"
#include "Input.h"

static std::wstring s_SolitaireTableauHeader =
LR"(#################################################
  |D|  -------  |1|    |2|    |3|    |4|    |5|  
#################################################)";

class Solitaire
{
public:
	//Plays the game
	static void PlayGame();
	//Returns a string representation of a deck face up
	static std::wstring LayoutDeckAsString(Deck& deck);
	//Returns a string representation of two strings printed out next to each other (first line of the second string will be appended to the first line of the first string etc.)
	static std::wstring AppendStringsOnSamePrintLine(const std::wstring& string1, const std::wstring& string2);
	//Returns a string represenatation of the deck
	static std::wstring DeckAsString(size_t size);
	//Returns a string of spaces that would fit the size of a card
	static std::wstring BlankCardSpace();
	//Returns whether or not the piles has a valid pair
	static bool HasAValidPair(std::vector<Card>& piles);
};