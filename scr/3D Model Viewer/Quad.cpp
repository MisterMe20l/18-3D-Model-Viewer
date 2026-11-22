#include "Quad.h"

float repeat = 4.0f; // Times to repeat

float quadVertices[] = {
	// Positions         // TexCoords (scaled)
	-0.5f, 0.0f, -0.5f,  0.0f,       0.0f,
	-0.5f, 0.0f,  0.5f,  0.0f,       repeat,
	 0.5f, 0.0f,  0.5f,  repeat,     repeat,

	 0.5f, 0.0f,  0.5f,  repeat,     repeat,
	 0.5f, 0.0f, -0.5f,  repeat,     0.0f,
	-0.5f, 0.0f, -0.5f,  0.0f,       0.0f
};


Quad::Quad() : VAO(0), VBO(0), modelMatrix(glm::mat4(1.0f)), shaderPtr(nullptr)
{
}

Quad::~Quad()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Quad::Init(Shader* shader)
{
	shaderPtr = shader;
	SetupMesh();

}

void Quad::Scale(float _x, float _y, float _z)
{
	modelMatrix = glm::scale(modelMatrix, glm::vec3(_x, _y, _z));
}

void Quad::Translate(float _x, float _y, float _z)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(_x, _y, _z));
}

void Quad::Draw(Camera* _Camera, Texture* _texture)
{
	if (!shaderPtr) return;

	glUseProgram(shaderPtr->programID);

	// Pass matrices to shader:
	GLint modelLoc = glGetUniformLocation(shaderPtr->programID, "model");
	GLint viewLoc = glGetUniformLocation(shaderPtr->programID, "view");
	GLint projLoc = glGetUniformLocation(shaderPtr->programID, "projection");

	glm::mat4 mvpMatrix = _Camera->GetProjectionMatrix() * _Camera->GetViewMatrix() * modelMatrix;
	GLint mvpLoc = glGetUniformLocation(shaderPtr->programID, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &mvpMatrix[0][0]);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &_Camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &_Camera->GetProjectionMatrix()[0][0]);

	// Bind texture:
	_texture->Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Quad::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	// Positions:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture Coordinates:
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
