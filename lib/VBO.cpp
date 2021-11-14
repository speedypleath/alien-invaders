#include <VBO.h>


VBO:VBO(GFloat *Vertices, GFloat *Colors, GLuint *Indices)
{
    this->Vertices = Vertices;
    this->Colors = Colors;
    this->Indices = Indices;
    glGenBuffers(1, &VerticesBufferId);
    // buffer pentru indici
    glGenBuffers(1, &IndicesBufferId);
    // se creeaza / se leaga un VAO (Vertex Array Object)
    glGenVertexArrays(1, &VaoId);
 
    // legare VAO
    glBindVertexArray(VaoId);

    // buffer-ul este setat ca buffer curent
    glBindBuffer(GL_ARRAY_BUFFER, VerticesBufferId);

    // buffer-ul va contine atat coordonatele varfurilor, cat si datele de culoare
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors) + sizeof(Vertices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertices), sizeof(Colors), Colors);

    // buffer-ul pentru indici
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
 
    // se activeaza lucrul cu atribute; atributul 0 = pozitie, atributul 1 = culoare, acestea sunt indicate corect in VBO
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(Vertices));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}
    
VBO:~VBO(){
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VerticesBufferId);
    glDeleteBuffers(1, &IndicesBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}
VBO:void bind(){
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}
VBO:void unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
