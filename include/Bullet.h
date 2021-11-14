#include <VBO.h>
#include <Shader.h>
#include "glm/glm.hpp"  

class Bullet {
private:
    float x;
    float y;
    int speed;
    float direction;
    Shader *shader;
    VBO *vbo;
    glm::mat4 position;
public:
    Bullet(float x, float y, int speed, float direction);
    ~Bullet();
    void draw();
};