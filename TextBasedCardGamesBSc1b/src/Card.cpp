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

std::wstring Card::GetCardAsString()
{
	std::wstring output;

	output = s_TemplateCard;

	switch (m_Number)
	{
	case 0:
		break;
	case 1:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'A';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'A';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 2:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'2';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'2';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 3:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'3';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'3';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 4:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'4';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'4';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 5:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'5';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'5';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 6:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'6';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'6';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 7:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'7';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'7';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 8:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'8';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'8';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 9:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'9';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'9';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 10:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'1';
			else if (output[i] == L'C')
				output[i] = L'0';
			else if (output[i] == L'D')
				output[i] = L'0';
			else if (output[i] == L'E')
				output[i] = L'1';
		}
		break;
	case 11:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'J';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'J';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 12:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'Q';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'Q';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	case 13:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'K';
			else if (output[i] == L'C')
				output[i] = L' ';
			else if (output[i] == L'D')
				output[i] = L'K';
			else if (output[i] == L'E')
				output[i] = L' ';
		}
		break;
	default:
		break;
	}

	switch (m_Suit)
	{
	case Suit::None:
		break;
	case Suit::Hearts:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'N')
				output[i] = L'\x2665';
		}
		break;
	case Suit::Diamonds:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'N')
				output[i] = L'\x2666';
		}
		break;
	case Suit::Clubs:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'N')
				output[i] = L'\x2663';
		}
		break;
	case Suit::Spades:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'N')
				output[i] = L'\x2660';
		}
		break;
	default:
		break;
	}

	return output;
}