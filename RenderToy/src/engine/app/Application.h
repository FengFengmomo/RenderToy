/*
* Class:
*	Application
* Description:
*	This class is the RenderToy itself, in the RenderToy, there're a Renderer and a Scene.
*	You first add models to Scene, then pass Scene and your shader to Renderer, then it 
*	will draw your models on the screen
*/

#pragma once

#include "core/Core.h"
#include "renderer/Renderer.h"
#include "scene/Scene.h"

class Application
{
private:
	GLFWwindow* m_Window;
	unsigned int m_Width;
	unsigned int m_Height;
	Renderer m_Renderer;
	Scene m_Scene;

	// This function updates frames, you should call it in your draw loop
	void Update();
	// Call this function in draw loop and it'll recive inputs from keyboard and move camera
	void CameraMove(GLFWwindow* window);

public:
	Application();
	~Application();

	// This function will set up RenderToy
	bool Init(unsigned int width, unsigned int height, const char* programName);
	void Run();
	
	void SetResolution(unsigned int width, unsigned int height);

	// Get RenderToy's members
	GLFWwindow* GetWindow();
	Renderer& GetRenderer();
	Scene& GetScene();

	void GetUI();
};