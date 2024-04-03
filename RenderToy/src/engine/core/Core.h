/*
* Description:
*	This header file contains every basic header file that is needed in this program, to keep things simple, you only need to include this header file instead of bunch of shits
*/

#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <map>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "spdlog/spdlog.h"

#define MIN_FOV 1.0f
#define MAX_FOV 100.0f

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

// Math
namespace core
{
    glm::mat4 GetRodrigue(glm::vec4 axis, float angle);
}