#pragma once

#include <GLEW/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak(); // C++ macro
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // usefull to wrap every line that could potentially give an error with this function

using namespace std;



void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);