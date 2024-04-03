/*
* -- Project --
*Title: 
*	RenderToy
*Description:
*	This is a simple renderer that allows you to test your shaders or other things.
*State:
*	In Development
*Version:
*	0.5.0
* 
* -- Dev --
* Name:
*	Nathan Song
* Email:
*	Nathan_Song_Zhijie@outlook.com
* Github:
*	https://github.com/LittleNate-Dev
*/

#include "app/Application.h"

Application renderToy;

// Handle Input
void BindInput();
void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void MouseMove(GLFWwindow* window, double xpos, double ypos);
void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
void WindowResize(GLFWwindow* window, int width, int height);
// Handle Input

int main(void)
{
	if (renderToy.Init(1280, 720, "RenderToy"))
	{
		spdlog::info("Start running RenderToy");
		BindInput();
		renderToy.Run();
	}
	else
	{
		spdlog::error("RenderToy Initialization failed!");
	}
	return 0;
}

void BindInput()
{
	GLCall(glfwSetScrollCallback(renderToy.GetWindow(), MouseScroll));
    GLCall(glfwSetKeyCallback(renderToy.GetWindow(), KeyboardInput));
	GLCall(glfwSetFramebufferSizeCallback(renderToy.GetWindow(), WindowResize));
	//GLCall(glfwSetCursorPosCallback(renderToy.GetWindow(), MouseMove));
}

void KeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void MouseMove(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << "xpos: " << xpos << std::endl;
	//std::cout << "ypos: " << ypos << std::endl;
}

void MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	renderToy.GetScene().GetCamera().SetFov(renderToy.GetScene().GetCamera().GetFov() - (float)yoffset*2.0f);
	if (renderToy.GetScene().GetCamera().GetFov() < MIN_FOV)
	{
		renderToy.GetScene().GetCamera().SetFov(MIN_FOV);
	}
	else if (renderToy.GetScene().GetCamera().GetFov() > MAX_FOV)
	{
		renderToy.GetScene().GetCamera().SetFov(MAX_FOV);
	}
	else
	{
		renderToy.GetScene().GetCamera().SetRotateSpeed(renderToy.GetScene().GetCamera().GetRotateSpeed() - (float)yoffset * 0.01f);
	}
	if (renderToy.GetScene().GetCamera().GetRotateSpeed() < 0.1f)
	{
		renderToy.GetScene().GetCamera().SetRotateSpeed(0.1f);
	}
	else if (renderToy.GetScene().GetCamera().GetRotateSpeed() > 10.0f)
	{
		renderToy.GetScene().GetCamera().SetRotateSpeed(10.0f);
	}
}

void WindowResize(GLFWwindow* window, int width, int height)
{
	renderToy.SetResolution(width, height);
	renderToy.GetScene().GetCamera().SetRes(width, height);
	renderToy.GetRenderer().Resize(width, height);
}