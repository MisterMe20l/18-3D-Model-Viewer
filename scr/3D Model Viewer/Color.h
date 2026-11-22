#pragma once
#include <vec3.hpp> 

typedef enum ConsoleColor
{
	GREEN = 10,
	RED = 12,
	YELLOW = 14,
	WHITE = 15
} unit;

struct Color
{
	float r, g, b;
	Color(float r, float g, float b) : r(r), g(g), b(b) {}
	Color(glm::vec3 color) : r(color.r), g(color.g), b(color.b) {}

	static const glm::vec3 white;
	static const glm::vec3 black;

	static const glm::vec3 red;
	static const glm::vec3 green;
	static const glm::vec3 blue;
	static const glm::vec3 yellow;
	static const glm::vec3 magenta;
	static const glm::vec3 cyan;

	static const glm::vec3 lightRed;
	static const glm::vec3 lightGreen;
	static const glm::vec3 lightBlue;
	static const glm::vec3 lightYellow;
	static const glm::vec3 lightMagenta;
	static const glm::vec3 lightCyan;
};