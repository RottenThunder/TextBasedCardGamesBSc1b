#include "Deck.h"
#include "Random.h"

Deck::Deck(bool isStandardDeck)
{
	if (!isStandardDeck)
		return;

	m_Cards.resize(52);

	uint32_t number = 0;
	Suit suit = Suit::None;
	for (int i = 0; i < 4; i++)
	{
		uint32_t suitID = (uint32_t)suit;
		suitID++;
		suit = (Suit)suitID;
		for (int j = 0; j < 13; j++)
		{
			number++;
			int index = (i * 13) + j;
			m_Cards[index].SetNumber(number);
			m_Cards[index].SetSuit(suit);
		}
		number = 0;
	}

	Shuffle();
}

void Deck::Shuffle()
{
	//TODO: Shuffle Cards Properly
	std::shuffle(m_Cards.begin(), m_Cards.end(), s_Engine);
}

Card Deck::Draw()
{
	Card topCard = m_Cards.front();
	m_Cards.erase(m_Cards.begin());
	return topCard;
}

void Deck::PlaceBottom(Card card)
{
	m_Cards.push_back(card);
}

void Deck::PlaceTop(Card card)
{
	m_Cards.insert(m_Cards.begin(), card);
}

size_t Deck::Size()
{
	return m_Cards.size();
}

Card& Deck::operator[](size_t index)
{
	return m_Cards[index];
}

const Card& Deck::operator[](size_t index) const
{
	return m_Cards[index];
}