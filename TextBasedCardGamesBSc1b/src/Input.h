#pragma once
#include <iostream>
#include <string>

static std::string s_Input = ""; //The Input that the player typed

//Gets Input from player
static void GetInput()
{
	std::cout << ">> ";
	std::getline(std::cin, s_Input);
}

//Gets input from player with a prompt
static void GetInput(const char* prompt)
{
	std::cout << prompt << std::endl;
	std::cout << ">> ";
	std::getline(std::cin, s_Input);
}