#pragma once
#include <vector>
#include <algorithm>
#include "Card.h"

class Deck
{
private:
	std::vector<Card> m_Cards;
public:
	Deck(bool isStandardDeck = false);

	void Shuffle();

	Card Draw();
	void PlaceBottom(Card card);
	void PlaceTop(Card card);
};