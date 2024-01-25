#include "Blackjack.h"

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

bool Blackjack::TakeAITurn(const std::string& AIName, Deck& deck, Deck& mainDeck)
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
			std::cout << AIName + " Has Hit" << std::endl;

			//See whether or not player has gone bust
			uint32_t minAIValue = Blackjack::GetMinValueOfHand(deck);
			if (minAIValue > 21)
			{
				AIHasGoneBust = true;
				std::cout << AIName + " Have Gone Bust" << std::endl;
			}
		}
		else
		{
			//Stand
			AIHasStanded = true;
			std::cout << AIName + " Has Standed" << std::endl;
		}
	}
	return AIHasGoneBust;
}