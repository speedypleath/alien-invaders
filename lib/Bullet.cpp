#include <Bullet.h>
#include <errorHandle.h>
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>

Bullet::Bullet(GLfloat x, GLfloat y, float speed, float direction, VAO *vao, Shader *shader) : x(x), y(y), speed(speed), direction(direction), shader(shader), vao(vao) {
    GLfloat vertices [] = {
        x,  y, 0.0f, 1.0f,                                                               1.0f, 1.0f, 1.0f,
        x + 35.0f * cos(direction), y + 35.0f * sin(direction), 0.0f, 1.0f,              1.0f, 1.0f, 1.0f,
    };
    GLuint indices [] = {
        0, 1
    };
    ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));
    vbo = new VBO(vertices, sizeof(vertices));
    vao->addBuffer(*vbo);
}

Bullet::~Bullet(){

}
void Bullet::draw(){
    shader->bind();
    ibo->bind();
    vbo->bind();
    vao->bind();
    glm::mat4 resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f/WIDTH, 1.f/HEIGHT, 1.0));
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-WIDTH, -HEIGHT, 0.0));
    glm::mat4 moveMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0));
    glm::mat4 myMatrix =  resizeMatrix * translateMatrix * moveMatrix;
    shader->setMat4("myMatrix", myMatrix);
    GLCall(glLineWidth(5.0f));
    GLCall(glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(0)));
}

bool Bullet::update(){
    if (x < 0 || x > 2 * WIDTH) {
        return false;
    }
    if (y < 0 || y > 2 * HEIGHT) {
        return false;
    }
    x += 0.1 * cos(direction);
    y += 0.1 * sin(direction);
    return true;
}

void Bullet::setPosition(GLfloat x){
    this->x = (x + WIDTH)/2; 
    this->y = 50.0f;
}

void Bullet::setDirection(float direction){
    this->direction = direction;
    vao->bind();
    shader->bind();
    ibo->bind();
    delete vbo;
    GLfloat vertices [] = {
        x,  y, 0.0f, 1.0f,                                                               1.0f, 1.0f, 1.0f,
        x + 35.0f * cos(direction), y + 35.0f * sin(direction), 0.0f, 1.0f,              1.0f, 1.0f, 1.0f,
    };
    vbo = new VBO(vertices, sizeof(vertices));
    vao->addBuffer(*vbo);
}