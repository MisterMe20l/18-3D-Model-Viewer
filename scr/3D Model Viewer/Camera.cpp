#include "Camera.h"

void Camera::Init(float _x = 0.0f, float _y = 0.5f, float _z = 0.0f)
{
	_position = glm::vec3(_x, _y, _z);
	_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = -90.0f;
	pitch = 0.0f;

	viewMatrix = glm::lookAt(_position, _position + _direction, _up);
	projectionMatrix = glm::perspective(glm::radians(fov), float(800) / 600, nearPlane, farPlane);
}

void Camera::Update(float _deltaTime, Framework* _Framework, Light* _Light)
{
	// Handle input-based translation
	float x = 0.0f, y = 0.0f, z = 0.0f;
	float toMove = 10.0f;

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) // Toggle mouse clamp
	{
		_Framework->SetMouseMode(mouseMode);
		mouseMode = !mouseMode;
	}

	if (!mouseMode)
	{
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) x = -toMove;
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) x = toMove;
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) z = toMove;
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) z = -toMove;
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Q)) y = toMove;
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E)) y = -toMove;

		Translate(x, y, z, _deltaTime);
		_Light->SetPos(_position.x, _position.y, _position.z);

		// Handle mouse-based rotation
		float sensitivity = 0.3f; 
		yaw += Input::GetInstance()->GetMouseDeltaX() * sensitivity;
		pitch -= Input::GetInstance()->GetMouseDeltaY() * sensitivity;
		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		// Recalculate direction vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		_direction = glm::normalize(front);

		// Recalculate view matrix
		viewMatrix = glm::lookAt(_position, _position + _direction, _up);
	}
}

void Camera::Translate(float _x, float _y, float _z, float _deltaTime)
{
	glm::vec3 right = glm::normalize(glm::cross(_direction, _up));
	glm::vec3 movement = _direction * _z + right * _x + _up * _y;
	_position += movement * _deltaTime * movSpeed;

	// Update view matrix after translation
	viewMatrix = glm::lookAt(_position, _position + _direction, _up);
}