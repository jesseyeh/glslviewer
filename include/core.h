#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <unistd.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image_write.h"

#include "postprocessor.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

class Core {
public:
    bool parseOpts(int argc, char *argv[]);

    int mainLoop();

private:
    bool init();
    bool initGLFW(int major = 3, int minor = 3);
    bool initWindow(GLFWwindow *&window);
    bool initGLAD();

    void createImageSequence();

    void processInput(GLFWwindow *window);

private:
    GLFWwindow *window_ = NULL;

    std::string usage_ = "Usage: glslviewer [-whf] [fragment]\n";

    int optWidth_  = 800;
    int optHeight_ = 600;

    bool optCreateImageSequence_ = false;
    unsigned int optTargetFrames_ = 0;
    unsigned int currFrame_ = 0;
    GLubyte *pixels_ = NULL;

    std::string fragmentPath_ = "";

    const float deltaTime_ = 0.0333f;
    float elapsedTime_ = 0.0f;
};

#endif

