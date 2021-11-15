#pragma once
#include <VBO.h>
#include <Shader.h>
#include <VAO.h>
#include <IndexBuffer.h>
#include "glm/glm.hpp"  

class Bullet {
private:
    GLfloat x;
    GLfloat y;
    float speed;
    float direction;
    Shader *shader;
    Shader *bulletShader;
    VBO *vbo;
    VAO *vao;
    IndexBuffer *ibo;
    glm::mat4 position;
public:
    Bullet(GLfloat x, GLfloat y, float speed, float direction,VAO *vao, Shader *shader);
    ~Bullet();
    void draw();
    bool update();
    inline VBO getVBO(){return *vbo;}
    inline GLfloat getX(){return x;}
    inline GLfloat getY(){return y;}
    void setPosition(GLfloat x);
    void setDirection(float direction);
};