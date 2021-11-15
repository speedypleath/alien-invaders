#pragma once
#include <VBO.h>
#include <GL/glew.h>

class VAO {
private:
    GLuint vao;
public:
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void addBuffer(VBO& vbo);
};