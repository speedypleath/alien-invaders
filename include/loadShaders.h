#pragma once
#include "GL/glew.h"
#include <string>
#include "glm/glm.hpp"  
class Shader
{
private:
    GLuint program;
public:
    Shader();
    ~Shader();
    std::string readFile(const char *filePath);
    GLuint loadShaders(const char *vertex_path, const char *fragment_path);
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const char *name, glm::mat4 value) const;
    inline GLuint getProgram() const { return program; }
};
