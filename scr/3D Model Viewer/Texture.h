#pragma once
#include "Debug.h"
#include <SDL3_image/SDL_image.h>
#include <GL/glew.h>
#include <string>
#include <common.hpp>

enum WrapMode
{
    Repeat = GL_REPEAT,
    Mirrored_Repeat = GL_MIRRORED_REPEAT,
    ClampToBoarder = GL_CLAMP_TO_BORDER,
    ClampToEdge = GL_CLAMP_TO_EDGE
};

enum MagFilterMode { 
    MagPoint = GL_NEAREST,
    MagBilinear = GL_LINEAR
};

enum MinFilterMode {
    MinPoint = GL_NEAREST,
    MinBilinear = GL_LINEAR,
    MinTrilinear0 = GL_NEAREST_MIPMAP_NEAREST,
    MinTrilinear1 = GL_LINEAR_MIPMAP_NEAREST,
    MinTrilinear2 = GL_NEAREST_MIPMAP_LINEAR,
    MinTrilinear3 = GL_LINEAR_MIPMAP_LINEAR
};

class Texture
{
public:
    void Init(std::string, WrapMode, MagFilterMode, MinFilterMode, int);
    void Load(std::string);
    void Bind();
    void Unbind();
    void Unload();
    const GLuint& ID = id;

private:
    GLuint id;
    GLsizei width, height;
    void* pixels;
    Uint8 depth;
    GLint format;
    SDL_Surface* data;

    WrapMode wrapMode;
    MagFilterMode magFilter;
    MinFilterMode minFilter;
    int anisoLevel;
};

