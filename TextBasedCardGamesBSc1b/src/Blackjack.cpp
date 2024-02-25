#include "Blackjack.h"

void Blackjack::PlayGame()
{
	int AIPlayersAmount = 0;

	GetInput(L"Enter the amount of AI Players to play against");
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
		for (size_t i = 0; i < playersDeck.Size(); i++)
			std::wcout << playersDeck[i].GetCardAsString() << std::endl;

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
				for (size_t j = 0; j < AIDecks[i].Size(); j++)
					std::wcout << AIDecks[i][j].GetCardAsString() << std::endl;
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
				std::wcout << L"You Have Won" << std::endl;
			}
			else
			{
				std::wcout << L"Player " << playersThatHaveHighestValue[i] + 2 << L" Have Won with a hand of:" << std::endl;
				for (size_t j = 0; j < AIDecks[playersThatHaveHighestValue[i]].Size(); j++)
					std::wcout << AIDecks[playersThatHaveHighestValue[i]][j].GetCardAsString() << std::endl;
				std::wcout << std::endl;
			}
		}
		if (playersThatHaveHighestValue.size() == 0)
		{
			std::wcout << L"The Dealer Has Won with a hand of:" << std::endl;
			for (size_t j = 0; j < dealersDeck.Size(); j++)
				std::wcout << dealersDeck[j].GetCardAsString() << std::endl;
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