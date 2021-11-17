#pragma once
#include "GL/glew.h"
#include <string>
#include "glm/glm.hpp"
  
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
