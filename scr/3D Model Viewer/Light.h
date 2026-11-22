#pragma once
#include "glm.hpp"
#include "GL\glew.h"

class Light
{
public:
    const glm::vec3& position = _position;
    const glm::vec3& ambient  = _ambient;
    const glm::vec3& diffuse  = _diffuse;
    const glm::vec3& specular = _specular;

    GLfloat attenuationConst;
    GLfloat attenuationLinear;
    GLfloat attenuationQuad;

    void Init(float, float, float);
    void Update(float);

    void Translate(float, float, float, float);
    void SetPos(float, float, float);

private:
    glm::vec3 _position;
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
};