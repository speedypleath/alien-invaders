#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:
    const GLuint *indices;
    GLuint count;
    GLuint vaoId;
    GLuint indicesBufferId;
public:
    IndexBuffer(const GLuint* indices, GLuint count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
};