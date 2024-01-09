#include "Card.h"

Card::Card()
	: m_Number(0), m_Suit(Suit::None)
{
}

uint32_t Card::GetNumber()
{
	return m_Number;
}

Suit Card::GetSuit()
{
	return m_Suit;
}

void Card::SetNumber(uint32_t number)
{
	if (number > 0 && number <= 13)
		m_Number = number;
}

void Card::SetSuit(Suit suit)
{
	if (suit != Suit::None)
		m_Suit = suit;
}

std::string Card::GetCardAsString()
{
	std::string output;

	switch (m_Number)
	{
	case 0:
		output.append("0");
		break;
	case 1:
		output.append("Ace");
		break;
	case 2:
		output.append("2");
		break;
	case 3:
		output.append("3");
		break;
	case 4:
		output.append("4");
		break;
	case 5:
		output.append("5");
		break;
	case 6:
		output.append("6");
		break;
	case 7:
		output.append("7");
		break;
	case 8:
		output.append("8");
		break;
	case 9:
		output.append("9");
		break;
	case 10:
		output.append("10");
		break;
	case 11:
		output.append("Jack");
		break;
	case 12:
		output.append("Queen");
		break;
	case 13:
		output.append("King");
		break;
	default:
		output.append("Unknown");
		break;
	}

	output.append(" of ");

	switch (m_Suit)
	{
	case Suit::None:
		output.append("None");
		break;
	case Suit::Hearts:
		output.append("Hearts");
		break;
	case Suit::Diamonds:
		output.append("Diamonds");
		break;
	case Suit::Clubs:
		output.append("Clubs");
		break;
	case Suit::Spades:
		output.append("Spades");
		break;
	default:
		output.append("Unknown");
		break;
	}

	return output;
}