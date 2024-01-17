#include <iostream>
#include "Deck.h"

static std::string s_Input = ""; //The Input that the player typed

//Gets Input from player
void GetInput()
{
	std::cout << ">> ";
	std::getline(std::cin, s_Input);
}

//Gets input from player with a prompt
void GetInput(const char* prompt)
{
	std::cout << prompt << std::endl;
	std::cout << ">> ";
	std::getline(std::cin, s_Input);
}

int main()
{
	int AIPlayersAmount = 0;

	GetInput("Enter the amount of AI Players to play against");
	AIPlayersAmount = std::stoi(s_Input);

	Deck mainDeck(true);
	Deck dealersDeck;
	Deck playersDeck;
	std::vector<Deck> AIDecks;
	AIDecks.resize(AIPlayersAmount);

	//Blackjack
	
	playersDeck.PlaceTop(mainDeck.Draw());
	for (int i = 0; i < AIDecks.size(); i++)
		AIDecks[i].PlaceTop(mainDeck.Draw());

	playersDeck.PlaceTop(mainDeck.Draw());
	for (int i = 0; i < AIDecks.size(); i++)
		AIDecks[i].PlaceTop(mainDeck.Draw());

	bool playerHasStanded = false;
	bool playerHasGoneBust = false;
	bool dealerHasStanded = false;
	bool dealerHasGoneBust = false;
	std::vector<bool> AIsHasStanded(AIDecks.size(), false);
	std::vector<bool> AIsHasGoneBust(AIDecks.size(), false);

	while (!playerHasStanded && !playerHasGoneBust)
	{
		//Players Turn
		std::cout << "\nYour Hand:\n";
		for (size_t i = 0; i < playersDeck.Size(); i++)
			std::cout << playersDeck[i].GetCardAsString() << std::endl;

		GetInput("Hit Or Stand? (H/S)");
		while (s_Input != "H" && s_Input != "S")
		{
			std::cout << "Invalid Input" << std::endl;
			GetInput("Hit Or Stand? (H/S)");
		}
		if (s_Input == "H")
		{
			//Hit
			playersDeck.PlaceTop(mainDeck.Draw());
			std::cout << "You Drawn " << playersDeck[0].GetCardAsString() << std::endl;
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
				std::cout << "You Have Gone Bust" << std::endl;
			}
		}
		else
		{
			//Stand
			playerHasStanded = true;
		}
	}

	//TODO: AIs Turns

	//Dealers Turns
	dealersDeck.PlaceTop(mainDeck.Draw());
	dealersDeck.PlaceTop(mainDeck.Draw());

	while (!dealerHasStanded && !dealerHasGoneBust)
	{
		bool dealerShouldHit = false;
		//TODO: Either Hit or Stand based on random chance


		if (dealerShouldHit)
		{
			//Hit
			dealersDeck.PlaceTop(mainDeck.Draw());
			std::cout << "The Dealer Has Hit" << std::endl;
			//See whether or not player has gone bust
			uint32_t minDealerValue = 0;
			for (size_t i = 0; i < dealersDeck.Size(); i++)
			{
				uint32_t cardNumber = dealersDeck[i].GetNumber();
				if (cardNumber > 10)
					cardNumber = 10;
				minDealerValue += cardNumber;
			}
			if (minDealerValue > 21)
			{
				dealerHasGoneBust = true;
				std::cout << "The Dealer Have Gone Bust" << std::endl;
			}
		}
		else
		{
			//Stand
			dealerHasStanded = true;
			std::cout << "The Dealer Has Standed" << std::endl;
		}
	}

	//Figure out who has won
	if (dealerHasGoneBust)
	{
		//TODO: Redo this bit
		if (playerHasGoneBust)
			std::cout << "You Have Lost" << std::endl;
		else
			std::cout << "You Have Won" << std::endl;

		for (size_t i = 0; i < AIDecks.size(); i++)
		{
			if (AIsHasGoneBust[i])
				std::cout << "Player " << i + 2 << " Have Lost" << std::endl;
			else
				std::cout << "Player " << i + 2 << " Have Won" << std::endl;
		}
	}
	else
	{
		uint32_t dealerValue = 0;
		uint32_t playerValue = 0;
		std::vector<uint32_t> AIValues(AIDecks.size(), 0);

		//Gets Dealer Value
		bool hasAce = false;
		for (size_t i = 0; i < dealersDeck.Size(); i++)
		{
			uint32_t cardNumber = dealersDeck[i].GetNumber();
			if (cardNumber == 1 && !hasAce)
				hasAce = true;
			if (cardNumber > 10)
				cardNumber = 10;
			dealerValue += cardNumber;
		}
		if (hasAce)
		{
			dealerValue += 10;
			if (dealerValue > 21)
				dealerValue -= 10;
		}

		//Gets Player Value
		hasAce = false;
		if (!playerHasGoneBust)
		{
			for (size_t i = 0; i < playersDeck.Size(); i++)
			{
				uint32_t cardNumber = playersDeck[i].GetNumber();
				if (cardNumber == 1 && !hasAce)
					hasAce = true;
				if (cardNumber > 10)
					cardNumber = 10;
				playerValue += cardNumber;
			}
			if (hasAce)
			{
				playerValue += 10;
				if (playerValue > 21)
					playerValue -= 10;
			}
		}

		//Gets AI Values
		for (size_t j = 0; j < AIDecks.size(); j++)
		{
			hasAce = false;
			if (!AIsHasGoneBust[j])
			{
				for (size_t i = 0; i < AIDecks[j].Size(); i++)
				{
					uint32_t cardNumber = AIDecks[j][i].GetNumber();
					if (cardNumber == 1 && !hasAce)
						hasAce = true;
					if (cardNumber > 10)
						cardNumber = 10;
					AIValues[j] += cardNumber;
				}
				if (hasAce)
				{
					AIValues[j] += 10;
					if (AIValues[j] > 21)
						AIValues[j] -= 10;
				}
			}
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
				std::cout << "You Have Won" << std::endl;
			else
				std::cout << "Player " << playersThatHaveHighestValue[i] + 2 << " Have Won" << std::endl;
		}
		if (playersThatHaveHighestValue.size() == 0)
			std::cout << "The Dealer Has Won" << std::endl;
	}

	GetInput("Press Enter To Quit");

	s_Input.clear();
	s_Input.shrink_to_fit();
}