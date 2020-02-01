#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "shader.h"

#define BUFFER_OFFSET(offset) ((void *)offset)

class PostProcessor {
public:
    PostProcessor(const std::string &fragmentPath);

    void draw(float time, int width, int height);

private:
    void initVAO();
    void initVBO();

private:
    Shader shader_;

    unsigned int vao_;
    unsigned int vbo_;

    inline constexpr static float vertices_[] = {
        -1.0f, -1.0f, // Bottom left
         1.0f,  1.0f, // Top right
        -1.0f,  1.0f, // Top left

        -1.0f, -1.0f, // Bottom left
         1.0f, -1.0f, // Bottom right
         1.0f,  1.0f  // Top right
    };

    const char *vertexSource_ = "#version 330 core\n"
                                "layout (location = 0) in vec2 vertex;\n"
                                "void main() {\n"
                                "    gl_Position = vec4(vertex.xy, 0.0f, 1.0f);\n"
                                "}\n\0";
};

#endif

