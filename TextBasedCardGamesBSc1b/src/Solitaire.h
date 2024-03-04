#pragma once
#include "Deck.h"
#include "Random.h"
#include "Input.h"

class Solitaire
{
public:
	//Plays the game
	static void PlayGame();
	//Returns whether or not the piles has a valid pair
	static bool HasAValidPair(std::vector<Card>& piles);
};