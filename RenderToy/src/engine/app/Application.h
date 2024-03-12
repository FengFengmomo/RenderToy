#pragma once

#include <glew\glew.h>
#include <glfw\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "gl/IndexBuffer.h"
#include "gl/VertexArray.h"
#include "gl/Shader.h"
#include "gl/VertexBufferLayout.h"
#include "gl/Renderer.h"
#include "gl/Texture.h"
#include "camera/Camera.h"
#include "panel/GUI.h"
#include "model/Model.h"

/*
* Class:
*	Application
* Description:
*	This class is the NateCraft itself
*
* Functions:
*	Init(int width, int height, const char* programName)
*	--Initialize program and opengl context, you need to designate the width and height of the program.
*
*	Run()
*	--Run the program ,basically everything this program can do will be included in this function.
*
*/
class Application
{
private:
	GLFWwindow* window;

	void Update();

public:
	Application();
	~Application();
	bool Init(int width, int height, const char* programName);
	void Run();
};