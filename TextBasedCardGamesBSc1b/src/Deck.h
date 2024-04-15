#pragma once
#include <vector>
#include <algorithm>
#include "Card.h"

class Deck
{
private:
	std::vector<Card> m_Cards;
	bool m_IsInfinite = false;
public:
	Deck(bool isStandardDeck = false, bool isInfinite = false);

	void Shuffle();

	Card Draw(); //Returns the card on top and removes it from the deck
	Card Draw(size_t index);
	void PlaceBottom(Card card);
	void PlaceTop(Card card);

	Card PeekTop(); //Returns a copy of the card on the top without removing it from the deck
	Card PeekBottom(); //Returns a copy of the card on the bottom without removing it from the deck

	size_t Size();

	Card& operator[](size_t index);
	const Card& operator[](size_t index) const;
};