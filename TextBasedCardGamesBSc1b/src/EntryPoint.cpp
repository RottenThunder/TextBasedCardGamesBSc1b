#include "Blackjack.h"
#include "Solitaire.h"

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT); //This is required to make the console output unicode characters

	bool playing = true;
	while (playing)
	{
		GetInput(L"Do you want to play Blackjack or Solitaire? (B/S)");
		if (s_Input == L"B")
			Blackjack::PlayGame();
		else if (s_Input == L"S")
			Solitaire::PlayGame();
		else
		{
			playing = false;
			break;
		}

		while (s_Input != L"Y" && s_Input != L"N")
		{
			GetInput(L"Do you want to continue playing? (Y/N)");
			if (s_Input == L"Y")
				playing = true;
			else if (s_Input == L"N")
				playing = false;
			else
			{
				std::wcout << L"ERROR: Please enter either Y or N" << std::endl;
			}
		}
	}

	GetInput(L"Press Enter To Quit");

	s_Input.clear();
	s_Input.shrink_to_fit();
}