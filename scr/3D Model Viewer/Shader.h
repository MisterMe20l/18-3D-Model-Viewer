#pragma once
#include "Debug.h"
#include <fstream>
#include <string>
#include <iostream>
#include "GL\glew.h"
#include <SDL3_image/SDL_image.h>

class Shader
{
public:
	Shader() = default;
	Shader(const Shader&) = default;
	Shader& operator = (const Shader&) = default;

	const GLuint& programID = shaderProgramID;

	void Init(std::string _folderPath);
	void Use() const;

	GLuint GetAttributeLocation(const GLchar*); 
	GLuint GetProgramID() const;

private:
	std::string vertexName, fragmentName;

	GLuint shaderProgramID;
	GLuint vertexShaderID, fragmentShaderID;

	void CreateShaderProgram();
	void CreateShaderObjects();
	void CompileShader(GLuint, std::string);
	void CompileShaders();
	void AttachShaders();
	void LinkShaderProgram();

	void DetachShaders();
	void DeleteShaders();
	void DestroyProgram();

	std::string ReadFile(std::string);
};

