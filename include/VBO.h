#pragma once
#include <GL/glew.h>

class VBO {
private:
    GLfloat *Vertices;
    GLuint VaoId;
    GLuint VerticesBufferId;
    GLuint ColorBufferId;
public:
    VBO();
    ~VBO();
    void bind();
    void unbind();
};