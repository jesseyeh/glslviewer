glslviewer
==========

**glslviewer** is a shader viewer for GLSL shaders.

Dependencies
------------

glslviewer only requires CMake 3.0 or later. Additional dependencies are located in the `deps/` directory:

* [glad](https://github.com/Dav1dde/glad) for OpenGL functions
* [glfw](https://github.com/glfw/glfw) for creating windows and handling inputs/events
* [glm](https://github.com/g-truc/glm) for linear algebra
* [stb](https://github.com/nothings/stb) for image operations

Usage
-----

`glslviewer [-whf] [path/to/fragment/shader]`

| Opt | Description |
| --- | ----------- |
| -w | Specifies the window width |
| -h | Specifies the window height |
| -f | Specifies the number of image sequence frames to render |