#include "Shader.h"
#include <vector>

void Shader::Init(std::string _folderPath)
{
	shaderProgramID = 0;
	vertexShaderID = 0;
	fragmentShaderID = 0;

	vertexName = _folderPath + ".vert";
	fragmentName = _folderPath + ".frag";

	CreateShaderProgram();
	CreateShaderObjects();
	CompileShaders();
	AttachShaders();
	LinkShaderProgram();
}

void Shader::Use() const
{
	glUseProgram(shaderProgramID);
}


GLuint Shader::GetAttributeLocation(const GLchar* _Name)
{
	return glGetAttribLocation(shaderProgramID, _Name);
}

GLuint Shader::GetProgramID() const
{
	return shaderProgramID;
}

void Shader::CreateShaderProgram()
{
	shaderProgramID = glCreateProgram();
	if (shaderProgramID == 0)
		Debug::LogError("Shader program could not be created!");
	else
		Debug::Log("Shader program was created successfully!");
}

void Shader::CreateShaderObjects()
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
		Debug::LogError("Vertex shader could not be created!");
	else
		Debug::Log("Vertex shader was created successfully!");

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0)
		Debug::LogError("Fragment shader could not be created!");
	else
		Debug::Log("Fragment shader was created successfully!");

}

void Shader::CompileShader(GLuint _shaderID, std::string _fileName)
{
	GLint compileResult;
	const GLchar* finalCode;

	std::string content = ReadFile(_fileName);
	finalCode = (const GLchar*)(content.c_str());
	glShaderSource(_shaderID, 1, &finalCode, nullptr);
	glCompileShader(_shaderID);

	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		Debug::LogError("Could not create shader for \"" + _fileName + "\"!");

		GLchar error[1000];
		GLsizei length = 1000;

		glGetShaderInfoLog(_shaderID, 1000, &length, error);
		Debug::LogError(error);
	}
	else
	{
		Debug::Log("Shader was created successfully for \"" + _fileName + "\"!");
	}
}

void Shader::CompileShaders()
{
	CompileShader(vertexShaderID, vertexName);
	CompileShader(fragmentShaderID, fragmentName);
}

void Shader::AttachShaders()
{
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
}

void Shader::LinkShaderProgram()
{
	GLint linkResult;

	glLinkProgram(shaderProgramID);

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		GLchar error[1000];
		GLsizei length = 1000;
		glGetProgramInfoLog(shaderProgramID, 1000, &length, error);
		Debug::LogError("The shader program did not link! " + (std::string)error);
	}
	else
	{
		Debug::Log("The shader program has linked successfully!");
		glUseProgram(shaderProgramID);
	}
}

void Shader::DetachShaders()
{
	glDetachShader(shaderProgramID, vertexShaderID);
	glDetachShader(shaderProgramID, fragmentShaderID);
}

void Shader::DeleteShaders()
{
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::DestroyProgram()
{
	glDeleteProgram(shaderProgramID);
}

std::string Shader::ReadFile(std::string _fileName)
{
	std::ifstream file(_fileName);

	std::string lineText;
	std::string finalString;

	if (!file.is_open())
	{
		Debug::LogError(_fileName + " could not be opened!");
		return "";
	}
	else
	{
		Debug::Log(_fileName + " was opened successfully!");
	}

	while (std::getline(file, lineText))
	{
		finalString += lineText + '\n';
	}

	file.close();
	return finalString;
}

