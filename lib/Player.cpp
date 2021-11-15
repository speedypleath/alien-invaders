#include <Player.h>
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <errorHandle.h>
#include <Bullet.h>

using namespace std;

Player::Player(){
    GLuint indices[] = {
        3, 2, 1,
        0, 3, 1,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
    };

    GLfloat vertices[] = {
        // player vertices
        450.0f,  75.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f,
        550.0f, 75.0f, 0.0f, 1.0f,      1.0f, 1.0f, 1.0f,
        550.0f,  105.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
        450.0f,  105.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,

        460.0f,  105.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
        460.0f,  115.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 
        540.0f,  115.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 
        540.0f,  105.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,

        490.0f,  115.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
        490.0f,  130.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
        510.0f,  130.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
        510.0f,  115.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
    };

    vao = new VAO();
    ibo = new IndexBuffer(indices, sizeof(indices) / sizeof(GLuint));
    vbo = new VBO(vertices, sizeof(vertices));
    shader = new Shader("res/simple_shader.vert", "res/simple_shader.frag");
    vao->addBuffer(*vbo);
}

Player::~Player(){
    delete ibo;
    delete vbo;
    delete shader;
    delete vao;
}

void Player::draw(){
    shader->bind();
    ibo->bind();
    vbo->bind();
    vao->bind();
    glm::mat4 resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f/WIDTH, 1.f/HEIGHT, 1.0));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0));
    glm::mat4 translatePlayerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0, 0.0));
    glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-WIDTH, -HEIGHT, 0.0));
    glm::mat4 translateToPlayer = glm::translate(glm::mat4(1.0f), glm::vec3(500 + x, 100, 0.0));
    glm::mat4 translateToCenter = glm::translate(glm::mat4(1.0f), glm::vec3(-500 - x, -100, 0.0));
    glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0, 0.0, 1.0));

    glm::mat4 myMatrix =  resizeMatrix * translateMatrix * translateToPlayer * rotateMatrix * translateToCenter * translatePlayerMatrix;
    shader->setMat4("myMatrix", myMatrix);
    GLCall(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(0)));

}

void Player::move(int key){
	switch (key) {
		case GLUT_KEY_LEFT:
            x -= x - 60 > -WIDTH ? 10 : 0;
            cout<<x<<endl;
			break;
		case GLUT_KEY_RIGHT:
            x += x + 60 < WIDTH ? 10 : 0;
            cout<<x<<endl;
			break;
	}
}

void Player::rotate(unsigned char key){
    switch (key) {
        case 'a' :
            rotation += rotation <= PI/8 ? PI/16 : 0;
            cout<<"rotation: "<<rotation<<endl;
            break;
        case 'd' :
            rotation -= rotation >= -PI/8 ? PI/16 : 0;
            cout<<"rotation: "<<rotation<<endl;
            break;
	}
    if (key == 27)
        exit(0);
}
