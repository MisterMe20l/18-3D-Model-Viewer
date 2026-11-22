#pragma once
#include "Framework.h"
#include "Input.h"
#include "Light.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Camera
{
public:
    void Init(float, float, float);
    void Update(float, Framework*, Light*);
    void Translate(float, float, float, float);

    // Add accessors for compatibility
    glm::mat4 GetViewMatrix() const { return viewMatrix; }
    glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }

    glm::vec3 GetPosition() const { return _position; }

private:
    glm::vec3 _position;
    glm::vec3 _direction;
    glm::vec3 _up;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    float movSpeed = 5.0f;
    bool mouseMode = false;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
