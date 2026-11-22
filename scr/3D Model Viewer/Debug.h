#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include "Color.h"

class Debug
{
public:
	static void Log(std::string);
	static void Log(const char*);
	static void Log(std::string, ConsoleColor);

	static void LogWarning(std::string);
	static void LogError(std::string);
};