#pragma once
#include <ext/vector_float3.hpp>
#include <ext/vector_float2.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

