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

Converting an image sequence to a `.gif` using FFmpeg
---------------------------------------------------------

The image sequence created with the `-f` opt can be converted into a `.gif` using FFmpeg:

```
COLORS := 24
RATE   := 30
START  := 0

gif:
	ffmpeg \
		-f image2 \
		-r $(RATE) \
		-start_number $(START) \
		-i ./out_%03d.png \
		-y \
		-vf palettegen=max_colors=$(COLORS) palette.png
	ffmpeg \
		-f image2 \
		-r $(RATE) \
		-start_number $(START) \
		-i ./out_%03d.png \
		-i palette.png \
		-filter_complex "scale=-1:-1:flags=lanczos[x];[x][1:v]paletteuse" \
		-r $(RATE) ./out.gif

	# Cleanup intermediate files
	rm -f palette.png
```
