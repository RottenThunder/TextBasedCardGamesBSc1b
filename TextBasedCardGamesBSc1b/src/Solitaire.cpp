#include "Solitaire.h"

void Solitaire::PlayGame()
{
	GetInput(LR"(Baroness Solitaire

		Rules: All Kings are taken out of the deck. Five cards are dealt in a row as the bases of the five piles in the tableau. The top cards of each pile are available for removal to the discard pile.

		The aim is to discard all the cards by removing any pairs of available cards that total 13. In this game, spot cards are taken at face value, Jacks are worth 11, Queens 12. So the following combinations of cards may be discarded:

		Queen and Ace
		Jack and 2
		10 and 3
		9 and 4
		8 and 5
		7 and 6
		When all available discards have been made, five fresh cards are dealt, one onto each pile in the tableau either filling a space or covering the existing card. The new top cards are available for play and, once again, any combinations totalling 13 are moved to the discard pile. When the top card of a pile is discarded, the card beneath becomes immediately available. Play continues in this way until there are only three cards left in hand; these are used as grace cards, being added to the end of the tableau, face up and side by side, and are available for play.

		The game is out when all cards have been discarded.)");

	Deck mainDeck(true);
	Deck Piles[5];

	//Take the kings out
	int kingsTakenOut = 0;
	size_t i = 0;
	while (kingsTakenOut < 4)
	{
		if (mainDeck[i].GetNumber() == 13)
		{
			mainDeck.Draw(i);
			kingsTakenOut++;
		}
		else
			i++;
	}

	GetInput(L"Press Enter to Draw 5 new cards into one of each pile");

	for (int i = 0; i < 5; i++)
		Piles[i].PlaceTop(mainDeck.Draw());

	//Figure out whether there is a pair

	std::vector<Card> availableCards;
	availableCards.resize(5);
	availableCards[0] = Piles[0][0];
	availableCards[1] = Piles[1][0];
	availableCards[2] = Piles[2][0];
	availableCards[3] = Piles[3][0];
	availableCards[4] = Piles[4][0];

	//Illustrate cards

	std::wstring availableCardsAsString = CombineCardsAsString(availableCards[0].GetCardAsString(), availableCards[1].GetCardAsString());
	availableCardsAsString = CombineCardsAsString(availableCardsAsString, availableCards[2].GetCardAsString());
	availableCardsAsString = CombineCardsAsString(availableCardsAsString, availableCards[3].GetCardAsString());
	availableCardsAsString = CombineCardsAsString(availableCardsAsString, availableCards[4].GetCardAsString());
	std::wcout << availableCardsAsString.c_str() << std::endl;

	//Keep the play loop going unless there is no available actions such as drawing or discarding

	bool hasAValidAction = HasAValidPair(availableCards) || mainDeck.Size() != 0;

	while (hasAValidAction)
	{
		//Play Loop

		//Prompt player to choose which 2 columns (1-5) they think are a pair and also give them the prompt to draw 5 new cards

		size_t firstColumn = UINT64_MAX;
		size_t secondColumn = UINT64_MAX;
		while (firstColumn == secondColumn)
		{
			firstColumn = UINT64_MAX;
			secondColumn = UINT64_MAX;
			while (firstColumn == UINT64_MAX)
			{
				GetInput(L"Choose First Column (1-5) (6 to draw 5 new cards): ");
				if (s_Input == L"1")
					firstColumn = 0;
				else if (s_Input == L"2")
					firstColumn = 1;
				else if (s_Input == L"3")
					firstColumn = 2;
				else if (s_Input == L"4")
					firstColumn = 3;
				else if (s_Input == L"5")
					firstColumn = 4;
				else if (s_Input == L"6")
					firstColumn = 5;
				else
					std::wcout << L"Invalid Input" << std::endl;
			}
			while (secondColumn == UINT64_MAX && firstColumn != 5)
			{
				GetInput(L"Choose Second Column (1-5): ");
				if (s_Input == L"1")
					secondColumn = 0;
				else if (s_Input == L"2")
					secondColumn = 1;
				else if (s_Input == L"3")
					secondColumn = 2;
				else if (s_Input == L"4")
					secondColumn = 3;
				else if (s_Input == L"5")
					secondColumn = 4;
				else
					std::wcout << L"Invalid Input" << std::endl;
			}
			if (firstColumn == secondColumn)
				std::wcout << L"You can not specify the same column twice" << std::endl;
		}

		//Verify the pair is correct

		if (firstColumn == 5)
		{
			for (int i = 0; i < 5; i++)
				Piles[i].PlaceTop(mainDeck.Draw());
		}
		else
		{
			if (availableCards[firstColumn].GetNumber() + availableCards[secondColumn].GetNumber() == 13)
			{
				Piles[firstColumn].Draw();
				Piles[secondColumn].Draw();
				std::wcout << "The valid pair has been discarded" << std::endl;
			}
			else
			{
				std::wcout << "That is not a vaild pair" << std::endl;
			}
		}

		//Figure out whether there is a pair (TODO: Check whether there is a card in that pile)

		availableCards[0] = Piles[0][0];
		availableCards[1] = Piles[1][0];
		availableCards[2] = Piles[2][0];
		availableCards[3] = Piles[3][0];
		availableCards[4] = Piles[4][0];

		//Illustrate cards (TODO: illustrate cards on top of each other)

		std::wstring availableCardsAsString = CombineCardsAsString(availableCards[0].GetCardAsString(), availableCards[1].GetCardAsString());
		availableCardsAsString = CombineCardsAsString(availableCardsAsString, availableCards[2].GetCardAsString());
		availableCardsAsString = CombineCardsAsString(availableCardsAsString, availableCards[3].GetCardAsString());
		availableCardsAsString = CombineCardsAsString(availableCardsAsString, availableCards[4].GetCardAsString());
		std::wcout << availableCardsAsString.c_str() << std::endl;

		//Keep the play loop going unless there is no available actions such as drawing or discarding

		hasAValidAction = HasAValidPair(availableCards) || mainDeck.Size() != 0;
	}

	//TODO: Figure out whether the player has won
}

std::wstring Solitaire::CombineCardsAsString(const std::wstring& card1, const std::wstring& card2)
{
	std::wstring output = card1;

	size_t i = 0, j = 0, k = 0;
	std::wstring insertion;
	for (; i < 7; i++)
	{
		if (i == 6)
		{
			while (j < card2.size())
			{
				insertion.push_back(card2[j]);
				j++;
			}
			j++;
			while (k < output.size())
				k++;
		}
		else
		{
			while (card2[j] != L'\n')
			{
				insertion.push_back(card2[j]);
				j++;
			}
			j++;
			while (output[k] != L'\n')
				k++;
		}
		output.insert(k, insertion);
		k += insertion.size() + 1;
		insertion.clear();
	}

	return output;
}

std::wstring Solitaire::LayoutDeckAsString(Deck& deck)
{
	std::wstring output;

	for (size_t i = 0; i < deck.Size(); i++)
	{
		size_t j = deck.Size() - i - 1;

		if (j == deck.Size() - 1)
			output.append(deck[j].GetCardAsString());
		else
		{
			std::wstring card = deck[j].GetCardAsString();
			size_t replaceIndex = i * 16;
			size_t k = 0;
			for (; k < 39; k++)
			{
				output[replaceIndex] = card[k];
				replaceIndex++;
			}
			for (; k < 56; k++)
			{
				output.push_back(card[k]);
			}
		}
	}

	return output;
}

std::wstring Solitaire::AppendStringsOnSamePrintLine(const std::wstring& string1, const std::wstring& string2)
{
	std::wstring output = string1;

	size_t string1Lines = 1;
	size_t string1MostCharactersOnLine = 0;
	size_t string1LastLineCharactersCount = 0;
	for (size_t i = 0; i < string1.size(); i++)
	{
		if (string1[i] == L'\n')
		{
			string1Lines++;

			if (string1LastLineCharactersCount > string1MostCharactersOnLine)
				string1MostCharactersOnLine = string1LastLineCharactersCount;

			string1LastLineCharactersCount = 0;
		}
		else
			string1LastLineCharactersCount++;
	}
	if (string1.size() == 0)
		string1Lines = 0;

	size_t string2Lines = 1;
	for (size_t i = 0; i < string2.size(); i++)
	{
		if (string2[i] == L'\n')
			string2Lines++;
	}
	if (string2.size() == 0)
		string2Lines = 0;

	if (string2Lines > string1Lines)
	{
		output.append(string2Lines - string1Lines, L'\n');
		string1Lines = string2Lines;
	}

	for (size_t i = 0; i < string1Lines; i++)
	{
		for (size_t j = 0; j < string1MostCharactersOnLine; j++)
		{
			size_t index = (i * string1MostCharactersOnLine) + i + j;
			if (index >= output.size())
				output.append(1, L' ');
			else if (output[index] == L'\n')
				output.insert(index, 1, L' ');
		}
	}

	size_t indexOfString1 = 0;
	size_t indexOfString2 = 0;
	for (size_t i = 0; i < string2Lines; i++)
	{
		bool foundNewLineCharacter = false;

		//Find the index in the first string to insert
		while (indexOfString1 < output.size())
		{
			if (output[indexOfString1] == L'\n')
			{
				foundNewLineCharacter = true;
				output.erase(indexOfString1, 1);
				break;
			}
			indexOfString1++;
		}

		//Insert characters in second string up until the end or until a new line character
		while (indexOfString2 < string2.size())
		{
			if (string2[indexOfString2] == L'\n')
			{
				foundNewLineCharacter = true;
				indexOfString2++;
				break;
			}
			output.insert(indexOfString1, 1, string2[indexOfString2]);
			indexOfString1++;
			indexOfString2++;
		}

		if (foundNewLineCharacter)
		{
			output.insert(indexOfString1, 1, L'\n');
			indexOfString1++;
		}
	}

	return output;
}

bool Solitaire::HasAValidPair(std::vector<Card>& piles)
{
	for (size_t y = 0; y < piles.size(); y++)
	{
		for (size_t x = 0; x < piles.size(); x++)
		{
			if (piles[y].GetNumber() + piles[x].GetNumber() == 13)
				return true;
		}
	}

	return false;
}