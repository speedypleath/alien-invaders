#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> 
#include <GL/freeglut.h>
#include <unistd.h>
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
  ProgramId;

 
glm::mat4 myMatrix, resizeMatrix, matrTransl, matrScale, matrRot; 

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
		case ' ' :
			break;
        case 'a' :
            break;
        case 'd' :
            break;
	}
    if (key == 27)
        exit(0);
}
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT :
			break;
		case GLUT_KEY_RIGHT :
			break;
		case GLUT_KEY_UP :
			break;
		case GLUT_KEY_DOWN :
			break;
	}
}

void CreateVBO(void)
{
  GLfloat Vertices[] = {

  };
   
 


  GLfloat Colors[] = {

  };
 


  glGenBuffers(1, &VboId);

  glBindBuffer(GL_ARRAY_BUFFER, VboId);

  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  

  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
 

  glGenBuffers(1, &ColorBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);

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
  ProgramId = LoadShaders("res/04_03_Shader.vert", "res/04_03_Shader.frag");
  glUseProgram(ProgramId);
}



void DestroyShaders(void)
{
  glDeleteProgram(ProgramId);
}
 
void Initialize(void)
{
  CreateVBO();
  CreateShaders();
}
void RenderFunction(void)
{

}
void Cleanup(void)
{
  DestroyShaders();
  DestroyVBO();
}


int main(int argc, char* argv[])
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowPosition (100,100); 
  glutInitWindowSize(800,600); 
  glutCreateWindow("Alien Invaders"); 
  glewInit(); 
  Initialize( );
//   glutDisplayFunc(RenderFunction);
//   glutIdleFunc(RenderFunction);
//   glutKeyboardFunc(processNormalKeys);
//   glutSpecialFunc(processSpecialKeys);
  glutCloseFunc(Cleanup);
  glutMainLoop();
  
  
}
