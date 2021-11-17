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
BulletManager *bulletManager;
float cooldown = 0.0f;


void processNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    if (key == ' '){
        if(cooldown <= 0.0f){
            bulletManager->shoot(player->getPosition(), PI/2 + player->getRotation());
            cooldown = 40.0f;
        }
    }
    else
        player->rotate(key);
}
void processSpecialKeys(int key, int x, int y) {
    player->move(key);
}
 
void initialize(void)
{
    player = new Player();
    bulletManager = new BulletManager();
    player->draw();
    bulletManager->draw();
}

void render(void)
{   
    cooldown -= 0.01f;
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    player->draw();
    bulletManager->draw();
    bulletManager->update();
    GLCall(glutSwapBuffers());
    GLCall(glFlush());
}
void cleanup(void)
{
    delete player;
    delete bulletManager;
}

int main(int argc, char* argv[])
{
    GLCall(glutInit(&argc, argv));
    GLCall(glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB));
    GLCall(glutInitWindowPosition (100,100)); 
    GLCall(glutInitWindowSize(1000,700)); 
    GLCall(glutCreateWindow("Alien Invaders")); 
    GLCall(glewInit()); 
    initialize();
    GLCall(glutDisplayFunc(render));
    GLCall(glutIdleFunc(render));
    GLCall(glutKeyboardFunc(processNormalKeys));
    GLCall(glutSpecialFunc(processSpecialKeys));
    GLCall(glutCloseFunc(cleanup));
    GLCall(glutMainLoop());
    return 0;
}