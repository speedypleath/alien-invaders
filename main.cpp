#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Shader.h>
#include <errorHandle.h>
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

GLuint
    VaoId,
    VerticesBufferId,
    ColorBufferId,
    IndicesBufferId,
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
 
    GLuint Indices[] = {
        3, 2, 1,
        0, 3, 1,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
    };

        // se creeaza un buffer nou pentru varfuri
    GLCall(glGenBuffers(1, &VerticesBufferId));
    // buffer pentru indici
    GLCall(glGenBuffers(1, &IndicesBufferId));
    // se creeaza / se leaga un VAO (Vertex Array Object)
    GLCall(glGenVertexArrays(1, &VaoId));
 
    // legare VAO
    GLCall(glBindVertexArray(VaoId));

    // buffer-ul este setat ca buffer curent
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VerticesBufferId));

    // buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Colors) + sizeof(Vertices), NULL, GL_STATIC_DRAW));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices));
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors));

    // buffer-ul pentru indici
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBufferId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW));
 
    // se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
    GLCall(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL));
    GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(Vertices)));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
 }
void DestroyVBO(void)
{
    GLCall(glDisableVertexAttribArray(1));
    GLCall(glDisableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glDeleteBuffers(1, &ColorBufferId));
    GLCall(glDeleteBuffers(1, &VerticesBufferId));
    GLCall(glDeleteBuffers(1, &IndicesBufferId));

    GLCall(glBindVertexArray(0));
    GLCall(glDeleteVertexArrays(1, &VaoId));
}

 
// void DestroyShaders(void)
// {
//     GLCall(glDeleteProgram(ProgramId));
// }

void ProcessNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
		case ' ' :
			break;
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
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f)); // culoarea de fond a ecranului
    CreateVBO();
}
void RenderPlayer(void)
{
    Shader shader = Shader("res/04_03_Shader.vert", "res/04_03_Shader.frag");
    myMatrix = glm::mat4(1.0f);
	resizeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.f/width, 1.f/height, 1.0));
    scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0));
    translatePlayerMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(playerX, 0.0, 0.0));
    translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-width, -height, 0.0));
    translateToPlayer = glm::translate(glm::mat4(1.0f), glm::vec3(500 + playerX, 100, 0.0));
    translateToCenter = glm::translate(glm::mat4(1.0f), glm::vec3(-500 - playerX, -100, 0.0));
    rotateMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0, 0.0, 1.0));

    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    myMatrix =  resizeMatrix * translateMatrix * translateToPlayer * rotateMatrix * translateToCenter * translatePlayerMatrix;
    shader.setMat4("myMatrix", myMatrix);
    GLCall(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void*)(0)));
    GLCall(glutSwapBuffers());
    GLCall(glFlush());
}
void Cleanup(void)
{
    DestroyVBO();
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
    GLCall(glutDisplayFunc(RenderPlayer));
    GLCall(glutIdleFunc(RenderPlayer));
    GLCall(glutKeyboardFunc(ProcessNormalKeys));
    GLCall(glutSpecialFunc(ProcessSpecialKeys));
    GLCall(glutCloseFunc(Cleanup));
    GLCall(glutMainLoop());
    return 0;
}
