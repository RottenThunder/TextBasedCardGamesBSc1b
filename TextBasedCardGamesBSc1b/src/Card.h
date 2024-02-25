#pragma once
#include <stdint.h>
#include <string>

enum Suit : uint32_t
{
	None = 0,
	Hearts = 1,
	Diamonds = 2,
	Clubs = 3,
	Spades = 4
};

static std::wstring s_TemplateCard = 
LR"(-------
|01   |
|     |
|  N  |
|     |
|   32|
-------)";

class Card
{
private:
	uint32_t m_Number;
	Suit m_Suit;
public:
	Card();

	uint32_t GetNumber();
	Suit GetSuit();
	void SetNumber(uint32_t number);
	void SetSuit(Suit suit);

	std::wstring GetCardAsString();
};