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

// =========
// parseOpts
// =========
bool Core::parseOpts(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << usage_;

        return false;
    }

    int opt;
    while ((opt = getopt(argc, argv, "w:h:")) != -1) {
        switch (opt) {
            case 'w':
                optWidth_ = atoi(optarg);
                break;
            case 'h':
                optHeight_ = atoi(optarg);
                break;
            case '?':
                std::cout << usage_;
                if (optopt == 'w' || optopt == 'h') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown option: -%c\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option: \\x%x\n", optopt);
                }
                return false;
            default:
                return false;
        }
    }

    if (argc - optind > 1) {
        std::cout << usage_;
        std::cerr << "More than one fragment shader was specified; proceeding with the last shader.\n";
    }
    for (int i = optind; i < argc; i++) {
        fragmentPath_ = std::string(argv[i]);
    }

    if (fragmentPath_.empty()) {
        std::cout << usage_;
        std::cerr << "No fragment shader was specified!\n";

        return false;
    }

    return true;
}

// ========
// mainLoop
// ========
int Core::mainLoop() {
    if (!init()) {
        return -1;
    }

    try {
        PostProcessor postProcessor(fragmentPath_);

        while (!glfwWindowShouldClose(window_)) {
            processInput(window_);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            postProcessor.draw(elapsedTime_, optWidth_, optHeight_);

            glfwSwapBuffers(window_);
            glfwPollEvents();

            elapsedTime_ += deltaTime_;
        }
    } catch (const char *e) {
        std::cerr << e;
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

