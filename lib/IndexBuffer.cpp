#include <IndexBuffer.h>
#include <errorHandle.h>

IndexBuffer::IndexBuffer(const GLuint *indices, GLuint count) : indices(indices), count(count)
{
    GLCall(glGenBuffers(1, &indicesBufferId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW));
}

    
IndexBuffer::~IndexBuffer(){
    GLCall(glDeleteBuffers(1, &indicesBufferId));
}
void IndexBuffer::bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, indicesBufferId));
}
void IndexBuffer::unbind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
