#include "Texture.h"

void Texture::Init(std::string _fileName, WrapMode _wrapMode, MagFilterMode _magFilter, MinFilterMode _minFilter, int _anisoLevel)
{
    glGenTextures(1, &id);

    this->wrapMode = _wrapMode;
    this->magFilter = _magFilter;
    this->minFilter = _minFilter;
    this->anisoLevel = _anisoLevel;

    data = nullptr;
    pixels = nullptr;

    Load(_fileName);
    Bind();
}

void Texture::Load(std::string _fileName)
{
    data = IMG_Load(_fileName.c_str());

    if (data == nullptr)
    {
        Debug::LogError("Could not load texture: " + _fileName);
        return;
    }

    width = data->w;
    height = data->h;
    pixels = (Uint8*)data->pixels;

    if (pixels == nullptr)
    {
        Debug::LogError("Could not read data from file: " + _fileName);
        return;
    }

    depth = data->format;
    format = (depth == 4) ? GL_RGBA : GL_RGB;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

    auto maxAnisoLevel = GL_MAX_TEXTURE_MAX_ANISOTROPY;
    anisoLevel = glm::clamp(anisoLevel, 1, maxAnisoLevel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, anisoLevel);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Unload()
{
    SDL_DestroySurface(data);
    glDeleteTextures(1, &id);
}
