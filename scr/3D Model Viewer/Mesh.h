#pragma once
#include "Vertex.h"
#include "Shader.h"
#include "Color.h"
#include "Debug.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"
#include <vector>
#include <GL/glew.h>
#include <assimp/SceneCombiner.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm.hpp>

class Mesh
{
public:
    Mesh();
    void Init(const char*, Shader*);

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<GLint> indices;
    std::vector<Vertex> vertices;

    void SetShader(Shader*);
    void Draw(Camera*, Light*, Texture*);
    void Update(float);
    void Translate(float, float, float);

protected:
    const aiScene* scene;
    Shader* shader;
    Material* material;
    GLuint vertexArrObjID;
    GLuint vboID;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    glm::mat4 model;
    glm::mat3 normal;
    glm::mat4 mvp;

    void LoadMesh(const char*);

    void Rotate(float, glm::vec3);
    void Scale(float, float, float);


    void CreateBuffers();
    void EnableAttribute(std::string, GLint, GLenum, GLboolean, GLsizei, const void*);

    void SetShaderProperty(const GLchar*, glm::mat4);
    void SetShaderProperty(const GLchar*, glm::mat3);
    void SetShaderProperty(const GLchar*, glm::vec3);
    void SetShaderProperty(const GLchar*, GLfloat);

    void CheckError404(GLuint, const GLchar*);
};

