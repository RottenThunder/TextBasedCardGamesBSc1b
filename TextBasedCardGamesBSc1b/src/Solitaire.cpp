#include "Solitaire.h"

void Solitaire::PlayGame()
{
	GetInput(LR"(Baroness Solitaire

		Rules: Five cards are dealt in a row as the bases of the five piles in the tableau. The top cards of each pile are available for removal to the discard pile.

		The aim is to discard all the cards by removing any Kings and pairs of available cards that total 13. In this game, spot cards are taken at face value, Jacks are worth 11, Queens 12, and Kings 13. So the following combinations of cards may be discarded:

		Queen and Ace
		Jack and 2
		10 and 3
		9 and 4
		8 and 5
		7 and 6
		Kings on their own.
		When all available discards have been made, five fresh cards are dealt, one onto each pile in the tableau either filling a space or covering the existing card.The new top cards are available for play and, once again, any Kings or combinations totalling 13 are moved to the discard pile.When the top card of a pile is discarded, the card beneath becomes immediately available.Play continues in this way until there are only two cards left in hand; these are used as grace cards, being added to the end of the tableau, face up and side by side, and are available for play.

		The game is out when all cards have been discarded.)");

	Deck mainDeck(true);
	Deck Piles[5];

	//Take the kings out
	int kingsTakenOut = 0;
	while (kingsTakenOut < 4)
	{
		size_t i = 0;
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

	bool hasAValidAction = true;

	while (hasAValidAction)
	{
		//Play Loop

		//Figure out whether there is a pair

		std::vector<Card> availableCards;
		availableCards.resize(5);
		availableCards[0] = Piles[0][0];
		availableCards[1] = Piles[1][0];
		availableCards[2] = Piles[2][0];
		availableCards[3] = Piles[3][0];
		availableCards[4] = Piles[4][0];

		if (!HasAValidPair(availableCards))
			break;

		//TODO: Keep the play loop going unless there is no available actions such as drawing or discarding

		//TODO: When ever the player pushes a certain key they will draw another 5 cards

		//TODO: Illustrate cards

		//TODO: Prompt player to choose which 2 columns (A-E) they think are a pair

		//TODO: Verify the pair is correct
	}

	//TODO: Figure out wether the player has won
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