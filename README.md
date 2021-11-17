# Alien Invaders
Space Invaders copy written in OpenGL.
## How to install 
```sh
mkdir build
cd build
cmake ..
make
```
Or you can just run 'CMake: Build' from vs code command palette.
## Build/Project structure
The game is installed using cmake 3.15.
```cmake
cmake_minimum_required(VERSION 3.15.0)
project(AlienInvaders VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "lib/*.cpp")
add_library(lib STATIC ${SOURCES})
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

if(WIN32)
    include("windows.h")
endif()

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} include)

add_executable(AlienInvaders main.cpp)

target_link_libraries(AlienInvaders ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} lib)

add_custom_target(CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res"
    COMMENT "Copy res directory to build tree" VERBATIM)

ADD_DEPENDENCIES (AlienInvaders CopyShaders)
```
A static library is created using .cpp files inside the lib folder and is added as a dependency, together with OpenGL, GLEW and GLUT. Include folder, containing headers, is added to the compiler's search paths. res folder is copied inside the build directory and added as a dependency.

![image](https://user-images.githubusercontent.com/61271015/142255263-1ce87542-2b1f-4cd4-9bc9-e9af0812d74e.png)

## Engine/Utility classes
Each class implements the basic functionality of binding and unbinding the component.
### 1) VBO
```c++
class VBO {
private:
    const void *vertices;
    GLuint vaoId;
    GLuint verticesBufferId;
public:
    VBO(const void* vertices, unsigned int size);
    ~VBO();
    void bind() const;
    void unbind() const;
    inline void setVAO(GLuint vao) { this->vaoId = vao; }
};
```
Represents an abstraction for vertex buffer objects.
### 2) VAO
```c++
class VAO {
private:
    GLuint vao;
public:
    VAO();
    ~VAO();
    void bind();
    void unbind();
    void addBuffer(VBO& vbo);
};
```
Represents an abstraction for vertex array objects, also implementing the functionality of adding VBOs. VBO template can't be customized yet, the function supposes that passed VBO 4-dimensional coordinates and 3-dimensional colour.
### 3) IndexBuffer
```c++
class IndexBuffer {
private:
    const GLuint *indices;
    GLuint count;
    GLuint vaoId;
    GLuint indicesBufferId;
public:
    IndexBuffer(const GLuint* indices, GLuint count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
};
```
Represents an abstraction for index buffer objects.
### 4) Shader
```c++
class Shader
{
private:
    GLuint program;
public:
    Shader(const char *vertex_path, const char *fragment_path);
    ~Shader();
    std::string readFile(const char *filePath);
    GLuint loadShaders(const char *vertex_path, const char *fragment_path);
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;
    void setMat4(const char *name, glm::mat4 value) const;
    void bind() const;
    void unbind() const;
};
```
Represents an abstraction for shaders, also implements the functionality of loading a shader from the file path. The class contains methods for transmitting values to the shaders, currently only for int, float and mat4.
## Error handling/Debugging
```c++
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
```
GLCall is a macro defined in errorHandle.h which can be used to wrap any OpenGL API call. It raises a SIGTRAP error when catching any OpenGL error, causing a breakpoint to appear when debugging the application. The function also logs the error code, by which function was the error triggered, in what file, at which line.
## Game objects
### 1) Player
```c++
class Player
{
private:
    Shader *shader;
    VAO *vao;
    VBO *vbo;
    IndexBuffer *ibo;
    glm::mat4 position;
    float x, rotation;
public:
    Player();
    ~Player();
    void draw();
    void move(int key);
    void rotate(unsigned char key);
    inline float getPosition(){return x;}
    inline float getRotation(){return rotation;}
};
```
The class renders the player and also manages its position. The player can move left and right using arrow keys, limited by the window boundaries, and can also rotate up to 45 degrees.

https://user-images.githubusercontent.com/61271015/142242609-009ed337-f25f-423a-a35d-5ef1f74aabdd.mp4

### 2) Bullet
```c++
class Bullet {
private:
    GLfloat x;
    GLfloat y;
    float speed;
    float direction;
    Shader *shader;
    Shader *bulletShader;
    VBO *vbo;
    VAO *vao;
    IndexBuffer *ibo;
    glm::mat4 position;
public:
    Bullet(GLfloat x, GLfloat y, float speed, float direction,VAO *vao, Shader *shader);
    ~Bullet();
    void draw();
    bool update();
    inline VBO getVBO(){return *vbo;}
    inline GLfloat getX(){return x;}
    inline GLfloat getY(){return y;}
    void setPosition(GLfloat x);
    void setDirection(float direction);
};
```
Each bullet is rendered on its own and can't be controlled by the player, once rendered it follows a set trajectory (starting point, direction and speed can be initialized) until it collides with another object (TODO) or is out of bounds.

https://user-images.githubusercontent.com/61271015/142244336-08daeb1c-d874-4a92-b81a-6713ec980110.mp4


### 3) BulletManager
```c++
class BulletManager
{
private:
    std::vector<Bullet*> bullets;
    Shader *bulletShader;
    VAO *bulletVAO;
    int currentBullet;
public:
    BulletManager();
    ~BulletManager();

    void update();
    void draw();
    void addBullet(Bullet *bullet);
    void shoot(float position, float direction);

    inline std::vector<Bullet*> getBullets(){ return bullets; }
};
```
The bullet manager is responsible for rendering and disposing of the bullets out of scope. It can also set a maximum number of bullets rendered at a time, preventing other objects from shooting when the threshold is reached. The bullet manager will cycle through every bullet when the method "shoot" is called, searching for an out of scope bullet and will rerender available bullets individually.


https://user-images.githubusercontent.com/61271015/142246416-277969db-799e-4197-806c-3a6ff87deb28.mp4

## Main program
### 1) processNormalKeys
```c++
void processNormalKeys(unsigned char key, int x, int y)
{
    if(key == ' '){
        if(cooldown <= 0.0f){
            bulletManager->shoot(player->getPosition(), PI/2 + player->getRotation());
            cooldown = 40.0f;
        }
    }
    else
        player->rotate(key);
}
```
The following 4 actions are controlled by normal keys:
 * exit game - Esc button
 * shoot - Space button, the bullet manager will render a bullet from the position of the player. This action has a set cooldown of 40 frames, meaning the player won't be able to shoot another bullet until the cooldown expires
 * rotate left - 'a' button, rotates the player PI/16 radians counterclockwise, the action is controlled by the player instance
 * rotate right - 'd' button, rotates the player PI/16 radians clockwise, also controlled by the player
### 2) processSpecialKeys
```c++
void processSpecialKeys(int key, int x, int y) {
    player->move(key);
}
```
Special keys are entirely controlled by the player instance:
  * move left - arrow key left, translates player position by x = -10
  * move right - arrow key right, translates player position by x = 10
### 3) initialize
```c++
void initialize(void)
{
    player = new Player();
    bulletManager = new BulletManager();
    player->draw();
    bulletManager->draw();
}
```
This function instantiates the player and the bullet manager, as well as renders them for the first time.
### 4) render
```c++
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
```
The bullet manager and the player will be rerendered every frame. Cooldown is also lowered here.
### 5) cleanup
```c++
void cleanup(void)
{
    delete player;
    delete bulletManager;
}
```
Deallocates player and bullet manager once the main loop ends.
### 6) main
```c++
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
```
The main function initialises glut and glew and starts the main loop.
