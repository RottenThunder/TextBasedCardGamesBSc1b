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
	//Returns whether or not the piles has a valid pair
	static bool HasAValidPair(std::vector<Card>& piles);
};