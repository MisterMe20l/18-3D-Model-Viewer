#include "Framework.h"

unsigned Framework::Init()
{
	int error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (error == -1)
		//Error message
		CheckCreationError(error);

	SetAttributes();
	error = MakeWindow();
	CheckCreationError(error);

	error = CreateContext();
	CheckCreationError(error);

	SetMouseMode(true);

	//Init GLEW
	error = glewInit();
	CheckCreationError(error);
	glEnable(GL_DEPTH_TEST);

	Debug::Log("GLEW version: " + std::string((const char*)glewGetString(GLEW_VERSION)));
}

void Framework::SetAttributes()
{
	//Set all OpenGL Atributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
}

void Framework::SetProperties()
{
	SetClearColor(Color::black);
	SetFrontfaceDir(GL_CCW);
	EnableFaceCulling(GL_BACK);
	EnableDepthTest();
}

unsigned Framework::MakeWindow()
{
	window = SDL_CreateWindow("3D Model Viewer", 1000, 750, SDL_WINDOW_OPENGL);

	return window != nullptr ? 0 : ERROR_WINDOW_INIT;
}

unsigned Framework::CreateContext()
{
	context = SDL_GL_CreateContext(window);

	return context != nullptr ? 0 : ERROR_CONTEXT_INIT;
}

void Framework::ClearScreenBuffers(GLenum _bufferTypes)
{
	glClear(_bufferTypes);
}

void Framework::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}

void Framework::Close()
{
	SDL_GL_DestroyContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Framework::EnableFaceCulling(GLenum _faceType)
{
	glEnable(GL_CULL_FACE);
	glCullFace(_faceType);
}

void Framework::SetFrontfaceDir(GLenum _faceDir)
{
	glFrontFace(_faceDir);
}

void Framework::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void Framework::SetClearColor(float _r, float _g, float _b)
{
	glClearColor(_r, _g, _b, 1.0f);
}

void Framework::SetClearColor(Color _color)
{
	glClearColor(_color.r, _color.g, _color.b, 1.0f);
}

void Framework::SetMouseMode(bool _clamp) 
{
	SDL_SetWindowRelativeMouseMode(window, _clamp);
}