#include "main.h"

int main(int argc, char* argv[])
{
	// Setup:
	Framework framework = {};
	framework.Init();
	framework.SetProperties();

	Camera* mainCamera = new Camera();
	mainCamera->Init(.0f, 1.5f, .0f);

	Light* light = new Light();
	light->Init(.0f, 1.5f, .0f);

	// Ground:
	Shader* groundShader = new Shader();
	groundShader->Init("shaders\\BasicColor");

	Quad* ground = new Quad();
	ground->Init(groundShader);
	ground->Scale(100.0f, 1.0f, 100.0f); 
	ground->Translate(0.0f, -0.1f, 0.0f);

	Texture* groundTexture = new Texture();
	groundTexture->Init("assets\\ground\\floor.jpg", WrapMode::Repeat, MagFilterMode::MagBilinear, MinFilterMode::MinBilinear, 1);

	// Object:
	Shader* objShader = new Shader();
	objShader->Init("shaders\\BasicTexture");

	Mesh* objMesh = new Mesh();
	objMesh->Init("assets\\cars\\car1\\Car.obj", objShader);

	Texture* objTexture = new Texture();
	objTexture->Init("assets\\cars\\car1\\car.png", WrapMode::Repeat, MagFilterMode::MagBilinear, MinFilterMode::MinBilinear, 1);
	objMesh->Translate(0, 0, -2);

	Uint32 previousTicks = SDL_GetTicks();
	Uint32 currentTicks = SDL_GetTicks();
	float deltaTime = 0;

	// Skybox:
	Skybox* skybox = new Skybox();
	std::vector<std::string> faces
	{
		"assets\\skybox\\right.png",
		"assets\\skybox\\left.png",
		"assets\\skybox\\top.png",
		"assets\\skybox\\bottom.png",
		"assets\\skybox\\front.png",
		"assets\\skybox\\back.png"
	};
	skybox->Init(faces);

	while (!Input::GetInstance()->ShouldCloseWindow())

	{
		currentTicks = SDL_GetTicks();
		deltaTime = static_cast<float>(currentTicks - previousTicks) / 1000.0f;
		//Debug::Log(deltaTime);

		// Update
		Input::GetInstance()->Update(deltaTime);
		mainCamera->Update(deltaTime, &framework, light);
		objMesh->Update(deltaTime);
		//light->Update(deltaTime);

		// Render
		framework.ClearScreenBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox->Draw(mainCamera);
		ground->Draw(mainCamera, groundTexture);
		objMesh->Draw(mainCamera, light, objTexture);

		// Swap buffer
		framework.SwapWindow();

		previousTicks = currentTicks;
	}
	delete mainCamera;
	delete light;
	delete groundShader;
	delete ground;
	delete groundTexture;
	delete objShader;
	delete objMesh;
	delete objTexture;
	delete skybox;

	framework.Close();

	return 0;
}