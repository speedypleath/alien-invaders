#pragma once
#include <GL/glew.h>

class VBO {
private:
    GLfloat *Vertices;
    GLfloat *Colors;
    GLuint *Indices;
    GLuint VaoId;
    GLuint VerticesBufferId;
    GLuint ColorBufferId;
    GLuint IndexBufferId;
public:
    VBO();
    ~VBO();
    void bind();
    void unbind();
};