#include "shader.h"

Shader::Shader() {
    programID_ = glCreateProgram();
}

// ============
// loadFromFile
// ============
bool Shader::loadFromFile(const std::string &shaderPath, GLenum shaderType) {
    std::ifstream file;

    // Ensure ifstream object can throw exceptions
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(shaderPath);

        std::stringstream stream;
        stream << file.rdbuf();

        file.close();

        std::string shaderSource = stream.str();

        return compile(shaderSource, shaderType);
    } catch (std::ifstream::failure e) {
        std::cerr << "Unable to load shader at path: " << "\"" << shaderPath << "\"\n";

        return false;
    }
}

// ==============
// loadFromSource
// ==============
bool Shader::loadFromSource(const std::string &shaderSource, GLenum shaderType) {
    return compile(shaderSource, shaderType);
}

// =======
// compile
// =======
bool Shader::compile(const std::string &shaderSource, GLenum shaderType) {
    int success;
    char infoLog[512];

    unsigned int shaderID = glCreateShader(shaderType);
    const char *shaderSource_c = shaderSource.c_str();
    glShaderSource(shaderID, 1, &shaderSource_c, NULL);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shaderID, sizeof(infoLog) / sizeof(*infoLog), NULL, infoLog);
        std::cerr << "Unable to compile shader: " << "\n\t" << infoLog << '\n';

        return false;
    }

    return link(shaderID);
}

// ====
// link
// ====
bool Shader::link(unsigned int shaderID) {
    glAttachShader(programID_, shaderID);
    glLinkProgram(programID_);

    int success;
    char infoLog[512];

    glGetProgramiv(programID_, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programID_, sizeof(infoLog) / sizeof(*infoLog), NULL, infoLog);
        std::cerr << "Unable to link shader program: " << "\n\t" << infoLog << '\n';
    }

    // Shader is now linked and is no longer needed
    glDeleteShader(shaderID);

    return success;
}

