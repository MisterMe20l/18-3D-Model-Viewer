#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Vertex.h"
#include "Texture.h"
#include <GL/glew.h>
#include <glm.hpp>
#include <vector>
#include <gtc/matrix_transform.hpp>


class Quad
{
public:
    Quad();
    ~Quad();

    void Init(Shader*);
    void Scale(float, float, float);
    void Translate(float, float, float);
    void Draw(Camera*, Texture*);

private:
    unsigned int VAO, VBO;
    glm::mat4 modelMatrix;
    Shader* shaderPtr;

    void SetupMesh(); 
};
