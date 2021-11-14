#include <Bullet.h>
#include <errorHandle.h>
#include "glm/gtc/matrix_transform.hpp"

Bullet::Bullet(float x, float y, int speed, float direction) : x(x), y(y), speed(speed), direction(direction) {
    GLfloat vertices [] = {
        x, y, 0.0f, 0.0f,                   1.0f, 1.0f, 1.0f,
        x + 5.0f, y + 5.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,
    };
    vbo = new VBO(vertices, sizeof(vertices));
    // shader = new Shader("res/simple_shader.vert", "res/simple_shader.frag");

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_TRUE, 7 * sizeof(GLfloat), (GLvoid*)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 7 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat))));
}

Bullet::~Bullet(){
    delete vbo;
    delete shader;
}
void Bullet::draw(){
    glm::mat4 resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f/WIDTH, 1.f/HEIGHT, 1.0));
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-WIDTH, -HEIGHT, 0.0));

    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    glm::mat4 myMatrix =  resizeMatrix * translateMatrix;
    shader->setMat4("myMatrix", myMatrix);
    GLCall(glLineWidth(5.0f));
    GLCall(glDrawArrays(GL_LINES, 0, 2));
    if (x < 0 || x > 2 * WIDTH) {
        delete this;
    }

    if (y < 0 || y > 2 * HEIGHT) {
        delete this;
    }
}