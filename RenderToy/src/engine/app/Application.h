/*
* Class:
*	Application
* Description:
*	This class is the RenderToy itself
*
* Functions:
*	Init(int width, int height, const char* programName)
*	--Initialize program and opengl context, you need to designate the width and height of the program.
*
*	Run()
*	--Run the program ,basically everything this program can do will be included in this function.
*
*/

#pragma once

#include "core/Core.h"
#include "shader/Shader.h"
#include "renderer/Renderer.h"
#include "texture/Texture.h"
#include "panel/GUI.h"
#include "model/Model.h"

class Application
{
private:
	GLFWwindow* window;
	int width;
	int height;
	Renderer renderer;

	void Update();
	void KeyboardInput(GLFWwindow* window);
	

public:
	Application();
	~Application();
	bool Init(int setWidth, int setHeight, const char* programName);
	void Run();
	
};