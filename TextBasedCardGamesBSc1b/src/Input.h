#pragma once
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>

static std::wstring s_Input = L""; //The Input that the player typed

//Gets Input from player
static void GetInput()
{
	std::wcout << L">> ";
	std::getline(std::wcin, s_Input);
}

//Gets input from player with a prompt
static void GetInput(const wchar_t* prompt)
{
	std::wcout << prompt << std::endl;
	std::wcout << L">> ";
	std::getline(std::wcin, s_Input);
}