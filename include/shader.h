#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader();

    bool loadFromFile(const std::string &shaderPath, GLenum shaderType);
    bool loadFromSource(const std::string &shaderSource, GLenum shaderType);

    void use() {
        glUseProgram(programID_);
    };

    inline void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(programID_, name.c_str()), value);
    }
    inline void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(programID_, name.c_str()), 1, &value[0]);
    }
    inline void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(programID_, name.c_str()), x, y);
    }

private:
    bool compile(const std::string &shaderSource, GLenum shaderType);
    bool link(unsigned int shaderID);

public:
    int programID_;
};

#endif

