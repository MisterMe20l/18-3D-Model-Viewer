#include "Debug.h"

void Debug::Log(std::string _message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
	std::cout << _message << std::endl;
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
}

void Debug::Log(const char* _Message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
	std::cout << _Message << std::endl;
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
}

void Debug::Log(std::string _message, ConsoleColor _color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, _color);
	std::cout << _message << std::endl;
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
}

void Debug::LogWarning(std::string _message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ConsoleColor::YELLOW);
	std::cout << _message << std::endl;
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
}

void Debug::LogError(std::string _message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ConsoleColor::RED);
	std::cerr << _message << std::endl;
	SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
}