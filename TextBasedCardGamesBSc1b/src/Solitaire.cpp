#include "Solitaire.h"

void Solitaire::PlayGame()
{
	GetInput(LR"(Baroness Solitaire

		Rules: All Kings are taken out of the deck. Five cards are dealt in a row as the bases of the 5 piles
		in the tableau. The top cards of each pile are available for removal to the discard pile.

		The aim is to discard all the cards by removing any pairs of available cards that total 13.
		In this game, spot cards are taken at face value, Jacks are worth 11, Queens 12.

		So the following combinations of cards may be discarded:

		Queen and Ace
		Jack and 2
		10 and 3
		9 and 4
		8 and 5
		7 and 6

		When all available discards have been made, five fresh cards are dealt,
		one onto each pile in the tableau either filling a space or covering the existing card.
		The new top cards are available for play and, once again, any combinations totalling 13
		are moved to the discard pile. When the top card of a pile is discarded, the card beneath
		becomes immediately available. Play continues in this way until there are only three cards
		left in hand; these are used as grace cards, being added to the end of the tableau,
		face up and side by side, and are available for play.

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

	//Renew the available cards

	std::vector<Card> availableCards;
	availableCards.resize(5);
	availableCards[0] = Piles[0].PeekTop();
	availableCards[1] = Piles[1].PeekTop();
	availableCards[2] = Piles[2].PeekTop();
	availableCards[3] = Piles[3].PeekTop();
	availableCards[4] = Piles[4].PeekTop();

	//Illustrate cards

	std::wcout << s_SolitaireTableauHeader << std::endl;
	std::wstring tableauAsString = AppendStringsOnSamePrintLine(DeckAsString(mainDeck.Size()), BlankCardSpace());
	tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[0]));
	tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[1]));
	tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[2]));
	tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[3]));
	tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[4]));
	std::wcout << tableauAsString << std::endl;

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
				GetInput(L"Choose First Column (1-5) (D to draw 5 new cards):");
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
				else if (s_Input == L"D" || s_Input == L"d")
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
			{
				Card card = mainDeck.Draw();
				if (card.GetNumber() != 0)
					Piles[i].PlaceTop(card);
			}
		}
		else
		{
			if (availableCards[firstColumn].GetNumber() + availableCards[secondColumn].GetNumber() == 13)
			{
				Piles[firstColumn].Draw();
				Piles[secondColumn].Draw();
				std::wcout << L"The valid pair has been discarded" << std::endl;
			}
			else
			{
				std::wcout << L"That is not a vaild pair" << std::endl;
			}
		}

		//Renew the available cards

		availableCards[0] = Piles[0].PeekTop();
		availableCards[1] = Piles[1].PeekTop();
		availableCards[2] = Piles[2].PeekTop();
		availableCards[3] = Piles[3].PeekTop();
		availableCards[4] = Piles[4].PeekTop();

		//Illustrate cards

		std::wcout << s_SolitaireTableauHeader << std::endl;
		tableauAsString = AppendStringsOnSamePrintLine(DeckAsString(mainDeck.Size()), BlankCardSpace());
		tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[0]));
		tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[1]));
		tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[2]));
		tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[3]));
		tableauAsString = AppendStringsOnSamePrintLine(tableauAsString, LayoutDeckAsString(Piles[4]));
		std::wcout << tableauAsString << std::endl;

		//Keep the play loop going unless there is no available actions such as drawing or discarding

		hasAValidAction = HasAValidPair(availableCards) || mainDeck.Size() != 0;
	}

	//Figure out whether the player has won
	
	if (availableCards[0].GetNumber() == 0 && availableCards[1].GetNumber() == 0 && availableCards[2].GetNumber() == 0 && availableCards[3].GetNumber() == 0 && availableCards[4].GetNumber() == 0)
		std::wcout << L"You have WON the game because you have no more available moves and there is no more cards on the table" << std::endl;
	else
		std::wcout << L"You have LOST the game because you have no more available moves and there is still cards on the table" << std::endl;
}

std::wstring Solitaire::LayoutDeckAsString(Deck& deck)
{
	std::wstring output;

	for (size_t i = 0; i < deck.Size(); i++)
	{
		size_t j = deck.Size() - i - 1;

		if (deck[j].GetNumber() == 0)
			continue;
		else if (j == deck.Size() - 1)
			output.append(deck[j].GetCardAsString());
		else
		{
			//Start from the previous cards first character + 2 lines

			std::wstring card = deck[j].GetCardAsString();
			size_t replaceIndex = i * 16;
			size_t k = 0;
			for (; k < 39; k++)
			{
				output[replaceIndex] = card[k];
				replaceIndex++;
			}
			for (; k < 55; k++)
			{
				output.push_back(card[k]);
			}
		}
	}

	if (deck.Size() == 0)
		output = BlankCardSpace();

	return output;
}

std::wstring Solitaire::AppendStringsOnSamePrintLine(const std::wstring& string1, const std::wstring& string2)
{
	std::wstring output = string1;

	//Found out the amount of lines and the most amount of characters on 1 line in the first string

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

	//Found out the amount of lines in the second string

	size_t string2Lines = 1;
	for (size_t i = 0; i < string2.size(); i++)
	{
		if (string2[i] == L'\n')
			string2Lines++;
	}
	if (string2.size() == 0)
		string2Lines = 0;

	//Add extra lines to the first string if the second string has more lines

	if (string2Lines > string1Lines)
	{
		output.append(string2Lines - string1Lines, L'\n');
		string1Lines = string2Lines;
	}

	//Add extra spaces to the end of lines in the first string to make each line have the same amount of characters 

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

	//Insert the lines in the second string to the first string

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

std::wstring Solitaire::DeckAsString(size_t size)
{
	std::wstring output = s_TemplateCard;

	for (int i = 0; i < output.size(); i++)
	{
		if (output[i] == L'N' || output[i] == L'D' || output[i] == L'E')
			output[i] = L' ';
	}

	size_t onesNumber = size % 10;
	size_t tensNumber = (size / 10) % 10;

	switch (tensNumber)
	{
	case 0:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'0';
		}
		break;
	case 1:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'1';
		}
		break;
	case 2:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'2';
		}
		break;
	case 3:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'3';
		}
		break;
	case 4:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'4';
		}
		break;
	case 5:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'5';
		}
		break;
	case 6:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'6';
		}
		break;
	case 7:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'7';
		}
		break;
	case 8:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'8';
		}
		break;
	case 9:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'B')
				output[i] = L'9';
		}
		break;
	default:
		break;
	}

	switch (onesNumber)
	{
	case 0:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'0';
		}
		break;
	case 1:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'1';
		}
		break;
	case 2:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'2';
		}
		break;
	case 3:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'3';
		}
		break;
	case 4:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'4';
		}
		break;
	case 5:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'5';
		}
		break;
	case 6:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'6';
		}
		break;
	case 7:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'7';
		}
		break;
	case 8:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'8';
		}
		break;
	case 9:
		for (int i = 0; i < output.size(); i++)
		{
			if (output[i] == L'C')
				output[i] = L'9';
		}
		break;
	default:
		break;
	}

	return output;
}

std::wstring Solitaire::BlankCardSpace()
{
	Card dummyCard;
	std::wstring output = dummyCard.GetCardAsString();
	for (size_t i = 0; i < output.size(); i++)
	{
		if (output[i] != L'\n')
			output[i] = L' ';
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