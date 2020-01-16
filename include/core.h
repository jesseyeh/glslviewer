#ifndef CORE_H
#define CORE_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

class Core {
public:
    int mainLoop();

private:
    bool init();
    bool initGLFW(int major = 3, int minor = 3);
    bool initWindow(GLFWwindow *&window);
    bool initGLAD();

    void processInput(GLFWwindow *window);

private:
    GLFWwindow *window_ = NULL;

    int optWidth_  = 800;
    int optHeight_ = 600;
};

#endif

