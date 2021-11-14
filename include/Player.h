#pragma once
#include "Shader.h"
#include "VBO.h"
#include "IndexBuffer.h"
#include "glm/glm.hpp"  

class Player
{
private:
    Shader *shader;
    VBO *vbo;
    IndexBuffer *ibo;
    GLuint vao;
    glm::mat4 position;
    float x, rotation;
public:
    Player();
    ~Player();
    void draw();
    void move(int key);
    void rotate(unsigned char key);
    void shoot();
};
