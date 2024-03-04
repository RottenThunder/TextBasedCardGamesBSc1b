#include "Deck.h"
#include "Random.h"

Deck::Deck(bool isStandardDeck, bool isInfinite)
{
	m_IsInfinite = isInfinite;

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
	//Fisher-Yates Algorithm
	for (size_t i = m_Cards.size() - 1; i > 0; i--)
	{
		size_t j = Random::GenerateRange64(i + 1);
		std::swap(m_Cards[j], m_Cards[i]);
	}
}

Card Deck::Draw()
{
	if (m_Cards.size() == 0 && m_IsInfinite)
	{
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
	else if (m_Cards.size() == 0)
		return Card();

	Card topCard = m_Cards.front();
	m_Cards.erase(m_Cards.begin());
	return topCard;
}

Card Deck::Draw(size_t index)
{
	Card card = m_Cards[index];
	m_Cards.erase(m_Cards.begin() + index);
	return card;
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