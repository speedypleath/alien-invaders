#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "loadShaders.h"

#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

GLuint
    VaoId,
    VboId,
    ColorBufferId,
    ProgramId,
    myMatrixLocation,
    scaleMatrixLocation,
    translateMatrixLocation,
    resizeMatrixLocation,
    codColLocation;
 
glm::mat4 
    myMatrix, 
    resizeMatrix,
    translateMatrix,
    scaleMatrix,
    rotateMatrix,
    translatePlayerMatrix,
    translateToPlayer,
    translateToCenter; 


int codCol;
float PI = 3.141592, rotation;
int width = 500, height = 350;
int playerX = 0;

void CreateVBO(void)
{
  // varfurile 
  GLfloat Vertices[] = {
    // vertices 
    0.0f, 0.0f, 0.0f, 1.0f,
    1000.0f, 0.0f, 0.0f, 1.0f,
    1000.0f, 700.0f, 0.0f, 1.0f,
    0.0f, 700.0f, 0.0f, 1.0f,
	// player vertices
    450.0f,  75.0f, 0.0f, 1.0f,
    550.0f, 75.0f, 0.0f, 1.0f,
	550.0f,  105.0f, 0.0f, 1.0f,
	450.0f,  105.0f, 0.0f, 1.0f,

	460.0f,  105.0f, 0.0f, 1.0f,
    460.0f,  115.0f, 0.0f, 1.0f,
    540.0f,  115.0f, 0.0f, 1.0f,
    540.0f,  105.0f, 0.0f, 1.0f,

    490.0f,  115.0f, 0.0f, 1.0f,
    490.0f,  130.0f, 0.0f, 1.0f,
    510.0f,  130.0f, 0.0f, 1.0f,
    510.0f,  115.0f, 0.0f, 1.0f,
  };

  GLfloat Colors[] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.0f, 0.5f, 1.0f,
  };
 

  // se creeaza un buffer nou
  glGenBuffers(1, &VboId);
  // este setat ca buffer curent
  glBindBuffer(GL_ARRAY_BUFFER, VboId);
  // punctele sunt "copiate" in bufferul curent
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  
  // se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  // se activeaza lucrul cu atribute; atributul 0 = pozitie
  glEnableVertexAttribArray(0);
  // 
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
 
  // un nou buffer, pentru culoare
  glGenBuffers(1, &ColorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // atributul 1 =  culoare
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
 }
void DestroyVBO(void)
{
 

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ColorBufferId);
  glDeleteBuffers(1, &VboId);

  glBindVertexArray(0);
  glDeleteVertexArrays(1, &VaoId);

   
}

void CreateShaders(void)
{
  ProgramId=LoadShaders("res/04_03_Shader.vert", "res/04_03_Shader.frag");
  glUseProgram(ProgramId);
}

 
void DestroyShaders(void)
{
    glDeleteProgram(ProgramId);
}

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
		case ' ' :
			break;
        case 'a' :
            rotation += rotation <= PI/8 ? PI/16 : 0;
            break;
        case 'd' :
            rotation -= rotation >= -PI/8 ? PI/16 : 0;
            break;
	}
    if (key == 27)
        exit(0);
}
void ProcessSpecialKeys(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT:
            playerX -= playerX - 60 > -width ? 10 : 0;
            cout<<playerX<<endl;
			break;
		case GLUT_KEY_RIGHT:
            playerX += playerX + 60 < width ? 10 : 0;
            cout<<playerX<<endl;
			break;
	}
}
 
void Initialize(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // culoarea de fond a ecranului
    CreateShaders();
    CreateVBO();
}
void RenderPlayer(void)
{
    myMatrix = glm::mat4(1.0f);
	resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
    scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0));
    translatePlayerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(playerX, 0.0, 0.0));
    translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-width, -height, 0.0));
    translateToPlayer = glm::translate(glm::mat4(1.0f), glm::vec3(500 + playerX, 100, 0.0));
    translateToCenter = glm::translate(glm::mat4(1.0f), glm::vec3(-500 - playerX, -100, 0.0));
    rotateMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0, 0.0, 1.0));

    glClear(GL_COLOR_BUFFER_BIT);

    myMatrix =  resizeMatrix * translateMatrix * translateToPlayer * rotateMatrix * translateToCenter * translatePlayerMatrix;
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix"); 
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE,  &myMatrix[0][0]);

    glDrawArrays(GL_POLYGON, 4, 4); 
    glDrawArrays(GL_POLYGON, 8, 4); 
    glDrawArrays(GL_POLYGON, 12, 4);

    glutSwapBuffers();
    glFlush();
}
void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition (100,100); 
    glutInitWindowSize(1000,700); 
    glutCreateWindow("Alien Invaders"); 
    glewInit(); 
    Initialize();
    glutDisplayFunc(RenderPlayer);
    glutIdleFunc(RenderPlayer);
    glutKeyboardFunc(ProcessNormalKeys);
    glutSpecialFunc(ProcessSpecialKeys);
    glutCloseFunc(Cleanup);
    glutMainLoop();
    return 0;
}
