#include "core.h"

// ====
// init
// ====
bool Core::init() {
    if (!initGLFW() || !initGLAD()) {
        return false;
    }

    glViewport(0, 0, optWidth_, optHeight_);

    glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);

    return true;
}

// ========
// initGLFW
// ========
bool Core::initGLFW(int major, int minor) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return initWindow(window_);
}

// ==========
// initWindow
// ==========
bool Core::initWindow(GLFWwindow *&window) {
    window = glfwCreateWindow(optWidth_, optHeight_, "glslviewer", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window!\n";
        glfwTerminate();

        return false;
    }
    glfwMakeContextCurrent(window);

    return true;
}

// ========
// initGLAD
// ========
bool Core::initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";

        return false;
    }

    return true;
}

// =======================
// framebufferSizeCallback
// =======================
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// ========
// mainLoop
// ========
int Core::mainLoop() {
    if (!init()) {
        return -1;
    }

    while (!glfwWindowShouldClose(window_)) {
        processInput(window_);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

// ============
// processInput
// ============
void Core::processInput(GLFWwindow *window) {
    if (window != NULL) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }
}

