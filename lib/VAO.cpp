#include <VAO.h>
#include <errorHandle.h>

VAO::VAO(){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}
VAO::~VAO(){
    GLCall(glDisableVertexAttribArray(1));
    GLCall(glDisableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GLCall(glBindVertexArray(0));
    GLCall(glDeleteVertexArrays(1, &vao));
}
void VAO::bind(){
    GLCall(glBindVertexArray(vao));
}
void VAO::unbind(){
    GLCall(glBindVertexArray(0));
}
void VAO::addBuffer(const VBO& vbo){
    vbo.bind();
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_TRUE, 7 * sizeof(GLfloat), (GLvoid*)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 7 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat))));
}
