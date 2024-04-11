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

	Card Draw();
	Card Draw(size_t index);
	void PlaceBottom(Card card);
	void PlaceTop(Card card);

	Card PeekTop();
	Card PeekBottom();

	size_t Size();

	Card& operator[](size_t index);
	const Card& operator[](size_t index) const;
};