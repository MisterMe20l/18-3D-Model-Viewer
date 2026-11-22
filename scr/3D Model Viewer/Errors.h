#pragma once
#define CheckCreationError(error) if (error != 0) return error;

typedef enum
{
	ERROR_FRAMEWORK_INIT = 10,
	ERROR_WINDOW_INIT = 20,
	ERROR_CONTEXT_INIT = 30,
	ERROR_GLEW_INIT = 40
} unsingned;