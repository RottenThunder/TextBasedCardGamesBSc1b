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
}