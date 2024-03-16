/*
* -- Project --
*Title: 
*	RenderToy
*Description:
*	This is a simple renderer that allows you to test your shaders or other things.
*State:
*	In Development
*Version:
*	0.0.1
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

int main(void)
{
	Application renderToy;
	if (renderToy.Init(960, 960, "RenderToy"))
	{
		std::cout << "Start running RenderToy" << std::endl;
		renderToy.Run();
	}
	else
	{
		std::cout << "RenderToy Initialization failed!" << std::endl;
	}
	return 0;
}