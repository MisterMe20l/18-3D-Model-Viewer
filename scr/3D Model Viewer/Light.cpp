#include "Light.h"
#include "Input.h"
#include <iostream>
#include "Debug.h"

void Light::Init(float _x = 0.0f, float _y = 0.5f, float _z = 0.0f)
{
	_position = glm::vec3(_x, _y, _z);
	_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	_diffuse = glm::vec3(0.1f, 0.1f, 0.1f);
	_specular = glm::vec3(0.1f, 0.1f, 0.1f);

	attenuationConst = 0.001f;
	attenuationLinear = 0.001f;
	attenuationQuad = 0.001f;
}

void Light::Translate(float _x, float _y, float _z, float _deltaTime)
{
	_position += glm::vec3(_x, _y, _z) * _deltaTime;
}

void Light::SetPos(float _x, float _y, float _z)
{
	_position = glm::vec3(_x, _y, _z);
}
