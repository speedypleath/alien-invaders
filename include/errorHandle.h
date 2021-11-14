#pragma once
#include <GL/glew.h>
#include <signal.h>


#define PI 3.14159265358979323846
#define HEIGHT 350
#define WIDTH  500
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
