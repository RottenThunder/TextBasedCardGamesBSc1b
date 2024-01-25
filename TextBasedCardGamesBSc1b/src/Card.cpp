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

	/*
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
	*/

	output = s_TemplateCard;

	switch (m_Number)
	{
	case 0:
		break;
	case 1:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = 'A';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = 'A';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 2:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '2';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '2';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 3:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '3';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '3';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 4:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '4';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '4';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 5:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '5';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '5';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 6:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '6';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '6';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 7:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '7';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '7';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 8:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '8';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '8';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 9:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '9';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = '9';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 10:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = '1';
			else if (output[i] == '1')
				output[i] = '0';
			else if (output[i] == '2')
				output[i] = '0';
			else if (output[i] == '3')
				output[i] = '1';
		}
		break;
	case 11:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = 'J';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = 'J';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 12:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = 'Q';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = 'Q';
			else if (output[i] == '3')
				output[i] = ' ';
		}
		break;
	case 13:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == '0')
				output[i] = 'K';
			else if (output[i] == '1')
				output[i] = ' ';
			else if (output[i] == '2')
				output[i] = 'K';
			else if (output[i] == '3')
				output[i] = ' ';
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
			if (output[i] == 'N')
				output[i] = '\3';
		}
		break;
	case Suit::Diamonds:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == 'N')
				output[i] = '\4';
		}
		break;
	case Suit::Clubs:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == 'N')
				output[i] = '\5';
		}
		break;
	case Suit::Spades:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == 'N')
				output[i] = '\6';
		}
		break;
	default:
		break;
	}

	return output;
}