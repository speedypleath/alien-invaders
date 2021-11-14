#pragma once
#include <GL/glew.h>

class VBO {
private:
    const void *vertices;
    GLuint vaoId;
    GLuint verticesBufferId;
public:
    VBO(const void* vertices, unsigned int size);
    ~VBO();
    void bind() const;
    void unbind() const;
};