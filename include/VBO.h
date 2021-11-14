#include <GL/glew.h>
#include <GL/freeglut.h>

class VBO {
private:
    GLfloat *Vertices;
    GLfloat *Colors;
    GLuint *Indices;
    GLuint VaoId;
    GLuint VerticesBufferId;
    GLuint ColorBufferId;
    GLuint IndexBufferId;
public:
    VBO(GFloat *Vertices, GFloat *Colors, GLuint *Indices);
    ~VBO();
    void bind();
    void unbind();
};