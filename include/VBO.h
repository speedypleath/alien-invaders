#pragma once
#include <GL/glew.h>

class VBO {
private:
    const void *vertices;
    GLuint vaoId;
    GLuint verticesBufferId;
public:
    VBO(const void* vertices);
    ~VBO();
    void bind() const;
    void unbind() const;
};