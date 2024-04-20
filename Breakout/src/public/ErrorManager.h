#pragma once

#include <glad/glad.h>
#include <gl/GL.h>

#include <iostream>


#define ASSERT(x) if (!(x)) __debugbreak();
#ifdef _DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogError(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif


void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function
            << " -> " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}
