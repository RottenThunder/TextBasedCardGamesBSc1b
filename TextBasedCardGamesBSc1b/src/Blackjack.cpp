#include "Blackjack.h"
#include <cwctype>

void Blackjack::PlayGame()
{
	int AIPlayersAmount = 0;

	bool validInput = false;

	while (!validInput)
	{
		GetInput(L"Enter the amount of AI Players to play against");

		for (size_t i = 0; i < s_Input.size(); i++)
		{
			validInput = true;
			if (!std::iswdigit(s_Input[i]))
			{
				validInput = false;
				std::wcout << "Invalid Input" << std::endl;
				i = s_Input.size();
			}
		}
	}

	AIPlayersAmount = std::stoi(s_Input);

	Deck mainDeck(true, true);
	Deck dealersDeck;
	Deck playersDeck;
	std::vector<Deck> AIDecks;
	AIDecks.resize(AIPlayersAmount);

	playersDeck.PlaceTop(mainDeck.Draw());
	for (int i = 0; i < AIDecks.size(); i++)
		AIDecks[i].PlaceTop(mainDeck.Draw());

	playersDeck.PlaceTop(mainDeck.Draw());
	for (int i = 0; i < AIDecks.size(); i++)
		AIDecks[i].PlaceTop(mainDeck.Draw());

	bool playerHasStanded = false;
	bool playerHasGoneBust = false;
	bool dealerHasGoneBust = false;
	std::vector<bool> AIsHasGoneBust(AIDecks.size(), false);

	while (!playerHasStanded && !playerHasGoneBust)
	{
		//Players Turn
		std::wcout << L"\nYour Hand:\n";
		std::wstring cardDeckAsString;
		for (size_t i = 0; i < playersDeck.Size(); i++)
			cardDeckAsString = AppendStringsOnSamePrintLine(cardDeckAsString, playersDeck[i].GetCardAsString());
		std::wcout << cardDeckAsString << std::endl;

		GetInput(L"Hit Or Stand? (H/S)");
		while (s_Input != L"H" && s_Input != L"S")
		{
			std::wcout << L"Invalid Input" << std::endl;
			GetInput(L"Hit Or Stand? (H/S)");
		}
		if (s_Input == L"H")
		{
			//Hit
			playersDeck.PlaceTop(mainDeck.Draw());
			std::wcout << L"You Drawn\n" << playersDeck[0].GetCardAsString() << std::endl;

			//See whether or not player has gone bust
			uint32_t minPlayerValue = 0;
			for (size_t i = 0; i < playersDeck.Size(); i++)
			{
				uint32_t cardNumber = playersDeck[i].GetNumber();
				if (cardNumber > 10)
					cardNumber = 10;
				minPlayerValue += cardNumber;
			}
			if (minPlayerValue > 21)
			{
				playerHasGoneBust = true;
				std::wcout << L"You Have Gone Bust" << std::endl;
			}
		}
		else
		{
			//Stand
			playerHasStanded = true;
		}
	}

	//AIs Turns
	for (size_t i = 0; i < AIDecks.size(); i++)
		AIsHasGoneBust[i] = Blackjack::TakeAITurn(L"Player " + std::to_wstring(i + 2), AIDecks[i], mainDeck);

	//Dealers Turns
	dealersDeck.PlaceTop(mainDeck.Draw());
	dealersDeck.PlaceTop(mainDeck.Draw());
	dealerHasGoneBust = Blackjack::TakeAITurn(L"The Dealer", dealersDeck, mainDeck);

	//Figure out who has won
	if (dealerHasGoneBust)
	{
		if (playerHasGoneBust)
			std::wcout << L"You Have Lost" << std::endl;
		else
			std::wcout << L"You Have Won" << std::endl;

		for (size_t i = 0; i < AIDecks.size(); i++)
		{
			if (!AIsHasGoneBust[i])
			{
				std::wcout << L"Player " << i + 2 << L" Have Won with a hand of:" << std::endl;
				std::wstring cardDeckAsString;
				for (size_t j = 0; j < AIDecks[i].Size(); j++)
					cardDeckAsString = AppendStringsOnSamePrintLine(cardDeckAsString, AIDecks[i][j].GetCardAsString());
				std::wcout << cardDeckAsString << std::endl;
				std::wcout << std::endl;
			}
		}
	}
	else
	{
		uint32_t dealerValue = 0;
		uint32_t playerValue = 0;
		std::vector<uint32_t> AIValues(AIDecks.size(), 0);

		//Gets Dealer Value
		dealerValue = Blackjack::GetMaxValueOfHand(dealersDeck);

		//Gets Player Value
		if (!playerHasGoneBust)
			playerValue = Blackjack::GetMaxValueOfHand(playersDeck);

		//Gets AI Values
		for (size_t j = 0; j < AIDecks.size(); j++)
		{
			if (!AIsHasGoneBust[j])
				AIValues[j] = Blackjack::GetMaxValueOfHand(AIDecks[j]);
		}

		//Who ever has higher than the dealer has a chance of winning
		std::vector<std::pair<size_t, uint32_t>> AllWinningValues;
		if (playerValue > dealerValue)
			AllWinningValues.push_back({ UINT64_MAX, playerValue });
		for (size_t i = 0; i < AIDecks.size(); i++)
		{
			if (AIValues[i] > dealerValue)
				AllWinningValues.push_back({ i, AIValues[i] });
		}

		//Figure out what is the highest value
		uint32_t highestValue = 0;
		for (size_t i = 0; i < AllWinningValues.size(); i++)
		{
			if (AllWinningValues[i].second > highestValue)
				highestValue = AllWinningValues[i].second;
		}

		//Figure out who has the highest value
		std::vector<size_t> playersThatHaveHighestValue;
		for (size_t i = 0; i < AllWinningValues.size(); i++)
		{
			if (AllWinningValues[i].second == highestValue)
				playersThatHaveHighestValue.push_back(AllWinningValues[i].first);
		}

		//Print out who won
		for (size_t i = 0; i < playersThatHaveHighestValue.size(); i++)
		{
			if (playersThatHaveHighestValue[i] == UINT64_MAX)
			{
				std::wcout << L"You Have Won with a hand of: " << std::endl;
				std::wstring cardDeckAsString;
				for (size_t i = 0; i < playersDeck.Size(); i++)
					cardDeckAsString = AppendStringsOnSamePrintLine(cardDeckAsString, playersDeck[i].GetCardAsString());
				std::wcout << cardDeckAsString << std::endl;
				std::wcout << std::endl;
			}
			else
			{
				std::wcout << L"Player " << playersThatHaveHighestValue[i] + 2 << L" Have Won with a hand of:" << std::endl;
				std::wstring cardDeckAsString;
				for (size_t j = 0; j < AIDecks[playersThatHaveHighestValue[i]].Size(); j++)
					cardDeckAsString = AppendStringsOnSamePrintLine(cardDeckAsString, AIDecks[playersThatHaveHighestValue[i]][j].GetCardAsString());
				std::wcout << cardDeckAsString << std::endl;
				std::wcout << std::endl;
			}
		}
		if (playersThatHaveHighestValue.size() == 0)
		{
			std::wcout << L"The Dealer Has Won with a hand of:" << std::endl;
			std::wstring cardDeckAsString;
			for (size_t j = 0; j < dealersDeck.Size(); j++)
				cardDeckAsString = AppendStringsOnSamePrintLine(cardDeckAsString, dealersDeck[j].GetCardAsString());
			std::wcout << cardDeckAsString << std::endl;
			std::wcout << std::endl;
		}
	}
}

uint32_t Blackjack::GetMinValueOfHand(Deck& deck)
{
	uint32_t value = 0;
	for (size_t i = 0; i < deck.Size(); i++)
	{
		uint32_t cardNumber = deck[i].GetNumber();
		if (cardNumber > 10)
			cardNumber = 10;
		value += cardNumber;
	}
	return value;
}

uint32_t Blackjack::GetMaxValueOfHand(Deck& deck)
{
	uint32_t value = 0;
	bool hasAce = false;
	for (size_t i = 0; i < deck.Size(); i++)
	{
		uint32_t cardNumber = deck[i].GetNumber();
		if (cardNumber == 1 && !hasAce)
			hasAce = true;
		if (cardNumber > 10)
			cardNumber = 10;
		value += cardNumber;
	}
	if (hasAce)
	{
		value += 10;
		if (value > 21)
			value -= 10;
	}
	return value;
}

bool Blackjack::TakeAITurn(const std::wstring& AIName, Deck& deck, Deck& mainDeck)
{
	bool AIHasStanded = false;
	bool AIHasGoneBust = false;
	while (!AIHasStanded && !AIHasGoneBust)
	{
		//Either Hit or Stand based on random chance
		bool AIShouldHit = false;
		uint32_t AIChanceToHit = Blackjack::GetMaxValueOfHand(deck);
		AIChanceToHit = 21 - AIChanceToHit;
		AIChanceToHit *= 10;
		AIShouldHit = Random::GeneratePercentageChance(AIChanceToHit);

		if (AIShouldHit)
		{
			//Hit
			deck.PlaceTop(mainDeck.Draw());
			std::wcout << AIName + L" Has Hit" << std::endl;

			//See whether or not player has gone bust
			uint32_t minAIValue = Blackjack::GetMinValueOfHand(deck);
			if (minAIValue > 21)
			{
				AIHasGoneBust = true;
				std::wcout << AIName + L" Have Gone Bust" << std::endl;
			}
		}
		else
		{
			//Stand
			AIHasStanded = true;
			std::wcout << AIName + L" Has Standed" << std::endl;
		}
	}
	return AIHasGoneBust;
}

std::wstring Blackjack::AppendStringsOnSamePrintLine(const std::wstring& string1, const std::wstring& string2)
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
