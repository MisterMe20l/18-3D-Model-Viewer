#pragma once
#include "Debug.h"
#include <glm.hpp>
#include <assimp/material.h>

class Material
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    void Init();
    void Init(const aiMaterial* _material);
};