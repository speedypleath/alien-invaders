#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Shader.h>
#include <VBO.h>
#include <IndexBuffer.h>
#include <errorHandle.h>
#include <Player.h>
#include <Bullet.h>
#include <BulletManager.h>
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
Player *player;
Bullet *bullet;
Shader *bulletShader;
VAO *bulletVAO;
BulletManager *bulletManager;

void ProcessNormalKeys(unsigned char key, int x, int y)
{
    if(key == ' '){
        bullet->setDirection(PI/2 + player->getRotation());
        bullet->setX(player->getPosition());
        bulletManager->addBullet(bullet);
    }
    else
        player->rotate(key);
}
void ProcessSpecialKeys(int key, int x, int y) {
    player->move(key);
}
 
void Initialize(void)
{
    player = new Player();
    bulletShader = new Shader("res/simple_shader.vert", "res/simple_shader.frag");
    bulletVAO = new VAO();
    bullet = new Bullet(WIDTH, 50.0f, 0.1, PI/2, bulletVAO, bulletShader);
    VBO bulletVBO = bullet->getVBO();
    bulletVAO->addBuffer(bulletVBO);
    bulletManager = new BulletManager();
    player->draw();
    bulletManager->draw();
}

void Render(void)
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    player->draw();
    bulletManager->draw();
    bulletManager->update();
    GLCall(glutSwapBuffers());
    GLCall(glFlush());
}
void Cleanup(void)
{
    delete player;
}

int main(int argc, char* argv[])
{
    GLCall(glutInit(&argc, argv));
    GLCall(glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB));
    GLCall(glutInitWindowPosition (100,100)); 
    GLCall(glutInitWindowSize(1000,700)); 
    GLCall(glutCreateWindow("Alien Invaders")); 
    GLCall(glewInit()); 
    Initialize();
    GLCall(glutDisplayFunc(Render));
    GLCall(glutIdleFunc(Render));
    GLCall(glutKeyboardFunc(ProcessNormalKeys));
    GLCall(glutSpecialFunc(ProcessSpecialKeys));
    GLCall(glutCloseFunc(Cleanup));
    GLCall(glutMainLoop());
    return 0;
}
