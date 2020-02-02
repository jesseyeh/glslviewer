#include "core.h"

int main(int argc, char *argv[]) {
    Core core;

    if (!core.parseOpts(argc, argv)) {
        return -1;
    }

    return core.mainLoop();
}

