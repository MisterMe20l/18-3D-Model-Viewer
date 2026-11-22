#include "Input.h"

Input* Input::GetInstance()
{
    static Input* instance = new Input();
    return instance;
}

void Input::Update(float _deltaTime)
{
    float x, y;
    SDL_GetRelativeMouseState(&x, &y);
    mouseDeltaX = x;
    mouseDeltaY = y;

    keyDown = keyUp = SDL_SCANCODE_UNKNOWN;
    mouseButtonDown = mouseButtonUp = -1;
    mouseDeltaX = mouseDeltaY = 0;

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
        case SDL_EVENT_KEY_DOWN:
            keyDown = events.key.scancode;
            break;

        case SDL_EVENT_KEY_UP:
            keyUp = events.key.scancode;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mouseButtonDown = events.button.button;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouseButtonUp = events.button.button;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            mouseDeltaX = events.motion.xrel;
            mouseDeltaY = events.motion.yrel;
            break;

        case SDL_EVENT_QUIT:
            closeWindow = true;
            break;

        default:
            break;
        }
    }
}

bool Input::ShouldCloseWindow() { return closeWindow; }

bool Input::GetKeyDown(SDL_Scancode _keyCode) { return keyDown == _keyCode; }

bool Input::GetKeyUp(SDL_Scancode keyCode) { return keyUp == keyCode; }

bool Input::GetMouseButtonDown(int _mouseButton) { return mouseButtonDown == _mouseButton; }

bool Input::GetMouseButtonUp(int _mouseButton) { return mouseButtonUp == _mouseButton; }

int Input::GetMouseDeltaX() const { return mouseDeltaX; }

int Input::GetMouseDeltaY() const { return mouseDeltaY; }
