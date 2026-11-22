#include "Skybox.h"
#include <SDL3_image/SDL_image.h>


Skybox::~Skybox()
{
    if (skyboxVAO) glDeleteVertexArrays(1, &skyboxVAO);
    if (skyboxVBO) glDeleteBuffers(1, &skyboxVBO);
    if (cubemapTexture) glDeleteTextures(1, &cubemapTexture);
}

void Skybox::Init(const std::vector<std::string>& _faces)
{
    // Load shader
    skyboxShader.Init("shaders\\skybox");

    // Setup cube geometry
    SetupCube();

    // Load cubemap texture
    cubemapTexture = LoadCubemap(_faces);

    // Configure shader
    skyboxShader.Use();
    GLint skyboxLoc = glGetUniformLocation(skyboxShader.GetProgramID(), "skybox");
    glUniform1i(skyboxLoc, 0);

}

void Skybox::SetupCube()
{
    float skyboxVertices[] = {
        // Positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

GLuint Skybox::LoadCubemap(const std::vector<std::string>& _faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, channels;
    for (GLuint i = 0; i < _faces.size(); i++)
    {
        SDL_Surface* surface = IMG_Load(_faces[i].c_str());
        if (!surface)
        {
            Debug::LogError("Failed to load cubemap texture at " + _faces[i] + ": " + SDL_GetError());
            continue;
        }

        Uint32 formatEnum = surface->format;
        int bpp = SDL_BYTESPERPIXEL(formatEnum);
        GLenum glFormat = (bpp == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0, glFormat,
            surface->w, surface->h, 0,
            glFormat,
            GL_UNSIGNED_BYTE,
            surface->pixels
        );

        SDL_DestroySurface(surface);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void Skybox::Draw(const Camera* _Camera)
{
    glDepthFunc(GL_LEQUAL);  // Change depth function so skybox passes depth test at depth=1.0

    skyboxShader.Use();

    // Remove translation from view matrix
    glm::mat4 view = glm::mat4(glm::mat3(_Camera->GetViewMatrix()));
    glm::mat4 projection = _Camera->GetProjectionMatrix();

    GLuint programID = skyboxShader.GetProgramID();
    glUniformMatrix4fv(glGetUniformLocation(programID, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "projection"), 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS); // Set depth function back to default
}
