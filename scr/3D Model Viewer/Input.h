#pragma once
#include "SDL3/SDL.h"

class Input
{
public:
    static Input* GetInstance();

    void Update(float);

    bool ShouldCloseWindow();
    bool GetKeyDown(SDL_Scancode);
    bool GetKeyUp(SDL_Scancode);
    bool GetMouseButtonDown(int);
    bool GetMouseButtonUp(int);

    int GetMouseDeltaX() const;
    int GetMouseDeltaY() const;

private:
    SDL_Event events;
    SDL_Scancode keyDown = SDL_SCANCODE_UNKNOWN;
    SDL_Scancode keyUp = SDL_SCANCODE_UNKNOWN;

    int mouseButtonDown = -1;
    int mouseButtonUp = -1;

    int mouseDeltaX = 0;
    int mouseDeltaY = 0;

    bool closeWindow = false;
};
