#pragma once
#include "Shader.h"
#include "VBO.h"
#include "VAO.h"
#include "IndexBuffer.h"
#include "glm/glm.hpp"  
#include <BulletManager.h>
#include <vector>
class Player
{
private:
    Shader *shader;
    VAO *vao;
    VBO *vbo;
    IndexBuffer *ibo;
    glm::mat4 position;
    float x, rotation;
public:
    Player();
    ~Player();
    void draw();
    void move(int key);
    void rotate(unsigned char key);
    inline float getPosition(){return x;}
    inline float getRotation(){return rotation;}
};
