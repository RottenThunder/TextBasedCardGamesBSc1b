#include "Blackjack.h"
#include "Solitaire.h"

int main()
{
	bool playing = true;
	while (playing)
	{
		GetInput("Do you want to play Blackjack or Solitaire? (B/S)");
		if (s_Input == "B")
			Blackjack::PlayGame();
		else if (s_Input == "S")
			Solitaire::PlayGame();
		else
		{
			playing = false;
			break;
		}

		while (s_Input != "Y" && s_Input != "N")
		{
			GetInput("Do you want to continue playing? (Y/N)");
			if (s_Input == "Y")
				playing = true;
			else if (s_Input == "N")
				playing = false;
			else
			{
				std::cout << "ERROR: Please enter either Y or N" << std::endl;
			}
		}
	}

	GetInput("Press Enter To Quit");

	s_Input.clear();
	s_Input.shrink_to_fit();
}