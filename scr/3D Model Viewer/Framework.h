#pragma once
#include <GL\glew.h>
#include <SDL3\SDL.h>
#include "Color.h"
#include "Errors.h"
#include "Debug.h"


class Framework
{
public:
	static int screenWidth;
	static int screenHeight;

	SDL_Window* window;
	SDL_GLContext context;

	unsigned Init();
	void SetAttributes();
	void SetProperties();
	unsigned MakeWindow();
	unsigned CreateContext();
	void ClearScreenBuffers(GLenum);
	void SwapWindow();
	void Close();

	void EnableFaceCulling(GLenum);
	void SetFrontfaceDir(GLenum);
	void EnableDepthTest();
	void SetClearColor(float, float, float);
	void SetClearColor(Color);
	void SetMouseMode(bool);
};