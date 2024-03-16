/*
* Description:
*	This header file contains every basic header file that is needed in this program, to keep things simple, you only need to include this header instead of bunch of shits
*/

#pragma once

#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);