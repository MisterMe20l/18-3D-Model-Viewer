#include "Material.h"

void Material::Init()
{
    ambient   = glm::vec3(1.f, 1.f, 1.f);
    diffuse   = glm::vec3(1.f, 1.f, 1.f);
    specular  = glm::vec3(1.f, 1.f, 1.f);
    shininess = .0f;
}

void Material::Init(const aiMaterial* _material)
{
    aiColor4D color;
    float value;

    if (AI_SUCCESS == aiGetMaterialColor(_material, AI_MATKEY_COLOR_AMBIENT, &color))
        ambient = glm::vec3(color.r, color.g, color.b);
    else
        Debug::LogError("Error getting ambient color from material");

    if (AI_SUCCESS == aiGetMaterialColor(_material, AI_MATKEY_COLOR_DIFFUSE, &color))
        diffuse = glm::vec3(color.r, color.g, color.b);
    else
        Debug::LogError("Error getting diffuse color from material");

    if (AI_SUCCESS == aiGetMaterialColor(_material, AI_MATKEY_COLOR_SPECULAR, &color))
        specular = glm::vec3(color.r, color.g, color.b);
    else
        Debug::LogError("Error getting specular color from material");

    if (AI_SUCCESS == aiGetMaterialFloat(_material, AI_MATKEY_SHININESS, &value))
        shininess = value;
    else
        Debug::LogError("Error getting shininess from material");
}