#include "Mesh.h"

Mesh::Mesh()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	model = glm::mat4(1.0);
	mvp = glm::mat4(1.0);
	normal = glm::mat3(1.0);

	shader = nullptr;
	vertexArrObjID = -1;
	vboID = -1;
}

void Mesh::Init(const char* _FilePath, Shader* _Shader)
{
	LoadMesh(_FilePath);

	// Shader
	this->shader = _Shader;
	CreateBuffers();

	EnableAttribute("positionIn", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	EnableAttribute("normalIn", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	EnableAttribute("texCoordIn", 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	// Material
	const C_STRUCT aiMaterial* aiMaterial = scene->mMaterials[scene->mMeshes[0]->mMaterialIndex];
	material = new Material();
	material->Init(aiMaterial);

	Rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Mesh::LoadMesh(const char* _FilePath)
{
	scene = aiImportFile(_FilePath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

	if (!scene)
	{
		Debug::LogError("Failed to load mesh: " + std::string(_FilePath));
		return;
	}

	positions.clear();

	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++)
	{
		const aiVector3D position = scene->mMeshes[0]->mVertices[i];
		positions.push_back(glm::vec3(position.x, position.y, position.z));
	}

	normals.clear();

	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++)
	{
		const aiVector3D normal = scene->mMeshes[0]->mNormals[i];
		normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
	}

	texCoords.clear();

	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++)
	{
		const aiVector3D texCoord = scene->mMeshes[0]->mTextureCoords[0][i];
		texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
	}

	indices.clear();

	for (int i = 0; i < scene->mMeshes[0]->mNumFaces; i++)
	{
		const aiFace face = scene->mMeshes[0]->mFaces[i];
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	vertices.clear();

	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position = positions[i];
		vertex.normal = normals[i];
		vertex.texCoords = texCoords[i];
		vertices.push_back(vertex);
	}
}

void Mesh::SetShader(Shader* _Shader)
{
	this->shader = _Shader;
	CreateBuffers();

	EnableAttribute("positionIn", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	EnableAttribute("normalIn", 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}

void Mesh::Draw(Camera* _Camera, Light* _Light, Texture* _Texture)
{
	glUseProgram(shader->programID);

	mvp = _Camera->GetProjectionMatrix() * _Camera->GetViewMatrix() * model;
	normal = glm::mat3(model);

	SetShaderProperty("mvp", mvp);
	SetShaderProperty("model", model);
	SetShaderProperty("normal", normal);

	SetShaderProperty("light.position", _Light->position);
	SetShaderProperty("light.ambient", _Light->ambient);
	SetShaderProperty("light.diffuse", _Light->diffuse);
	SetShaderProperty("light.specular", _Light->specular);

	SetShaderProperty("light.attenuationConst", _Light->attenuationConst);
	SetShaderProperty("light.attenuationLinear", _Light->attenuationLinear);
	SetShaderProperty("light.attenuationQuad", _Light->attenuationQuad);

	SetShaderProperty("material.ambient", material->ambient);
	SetShaderProperty("material.diffuse", material->diffuse);
	SetShaderProperty("material.specular", material->specular);
	SetShaderProperty("material.shininess", material->shininess);

	SetShaderProperty("cameraPosition", _Camera->GetPosition());

	glBindVertexArray(vertexArrObjID);
	glBindTexture(GL_TEXTURE_2D, _Texture->ID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _Texture->ID);

	// Set mainTex uniform
	GLuint texLoc = glGetUniformLocation(shader->programID, "mainTex");
	if (texLoc != -1) glUniform1i(texLoc, 0);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Mesh::Translate(float _x, float _y, float _z)
{
	position += glm::vec3(_x, _y, _z);
	model = glm::translate(model, glm::vec3(_x, _y, _z));
}

void Mesh::Rotate(float _angle, glm::vec3 _axis)
{
	rotation += _axis * _angle;
	model = glm::rotate(model, glm::radians(_angle), _axis);
}

void Mesh::Scale(float _x, float _y, float _z)
{
	scale = glm::vec3(_x, _y, _z);
	model = glm::scale(model, scale);
}

void Mesh::Update(float _deltaTime)
{
	//Rotate(10.0f * _deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Mesh::CreateBuffers()
{
	vertexArrObjID;
	glGenVertexArrays(1, &vertexArrObjID);
	glBindVertexArray(vertexArrObjID);

	// Vertex buffer object //

	GLuint bufferID; // Create
	glGenBuffers(1, &bufferID);
	vboID = bufferID;
	glBindBuffer(GL_ARRAY_BUFFER, bufferID); // Bind
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); // Fill

	// Element buffer object //

	GLuint indexBufferID; // Create
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID); // Bind
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLint), indices.data(), GL_STATIC_DRAW); // Fill

	if (indices.empty() || vertices.empty())
	{
		Debug::LogError("No mesh data to draw!");
		return;
	}

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::EnableAttribute(std::string _attributeName, GLint _size, GLenum _type,
	GLboolean _normalized, GLsizei _stride, const void* _Pointer)
{
	glBindVertexArray(vertexArrObjID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	const GLchar* name = (const GLchar*)(_attributeName.c_str());
	GLuint attributeID = glGetAttribLocation(shader->programID, name);
	if (attributeID == -1)
	{
		std::string message = "The attribute \"";
		message.append(_attributeName).append("\" does not exist or is unused!");
		Debug::LogWarning(message);
		return;
	}

	// Link and activate attribute
	glVertexAttribPointer(attributeID, _size, _type, _normalized, _stride, _Pointer);
	glEnableVertexAttribArray(attributeID);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::SetShaderProperty(const GLchar* _PropertyName, glm::mat4 _value)
{
	GLuint propertyID = -1;
	propertyID = glGetUniformLocation(shader->programID, _PropertyName);
	if (propertyID == -1)
	{
		std::string message = "The property \"";
		message.append(_PropertyName).append("\" does not exist or is unused");
		Debug::LogWarning(message);
		return;
	}
	glUniformMatrix4fv(propertyID, 1, GL_FALSE, &(_value[0][0]));
}

void Mesh::SetShaderProperty(const GLchar* _PropertyName, glm::mat3 _value)
{
	GLuint propertyID = -1;
	propertyID = glGetUniformLocation(shader->programID, _PropertyName);
	if (propertyID == -1)
	{
		std::string message = "The property \"";
		message.append(_PropertyName).append("\" does not exist or is unused");
		Debug::LogWarning(message);
		return;
	}
	glUniformMatrix3fv(propertyID, 1, GL_FALSE, &(_value[0][0]));
}

void Mesh::SetShaderProperty(const GLchar* _PropertyName, glm::vec3 _value)
{
	GLuint propertyID = -1;
	propertyID = glGetUniformLocation(shader->programID, _PropertyName);
	if (propertyID == -1)
	{
		std::string message = "The property \"";
		message.append(_PropertyName).append("\" does not exist or is unused");
		Debug::LogWarning(message);
		return;
	}
	glUniform3fv(propertyID, 1, &(_value.x));
}

void Mesh::SetShaderProperty(const GLchar* _PropertyName, GLfloat _value)
{
	GLuint propertyID = -1;
	propertyID = glGetUniformLocation(shader->programID, _PropertyName);
	if (propertyID == -1)
	{
		std::string message = "The property \"";
		message.append(_PropertyName).append("\" does not exist or is unused");
		Debug::LogWarning(message);
		return;
	}
	glUniform1f(propertyID, _value);
}

void Mesh::CheckError404(GLuint _attributeTypeID, const GLchar* _AttributeName)
{
	if (_attributeTypeID == -1)
	{
		std::string message = "The attribute \"";
		message.append(_AttributeName).append("\" does not exist.");
		Debug::LogError(message);
	}
}