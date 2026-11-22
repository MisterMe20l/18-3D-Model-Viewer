#pragma once
#include "Shader.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3_image/SDL_image.h>
#include "GL/glew.h"


class Skybox
{
public:
    Skybox() = default;
    ~Skybox();

    // Initialize: right, left, top, bottom, front, back
    void Init(const std::vector<std::string>&);

    // Render
    void Draw(const Camera*);

private:
    GLuint skyboxVAO = 0;
    GLuint skyboxVBO = 0;
    GLuint cubemapTexture = 0;
    Shader skyboxShader;

    GLuint LoadCubemap(const std::vector<std::string>&);
    void SetupCube();
    void FlipSurfaceVertical(SDL_Surface*);
};
