#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"


namespace gui
{
	void Init(GLFWwindow* window, const char* glVersion);
	void NewFrame();
	void EndFrame();
	void Destroy();

	void SameLine();

	void Begin(const char* label);
	bool SliderInt(const char* label, int* var, int min, int max);
	bool SliderFloat(const char* label, float* var, float min, float max);
	bool Button(const char* label);
	bool Checkbox(const char* label, bool* value);
	void End();

	void Draw();
}

