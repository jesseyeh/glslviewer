cmake_minimum_required(VERSION 3.0)
project(glslviewer)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(deps/glfw)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
    if (NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif ()
endif ()

include_directories(include/
                    deps/glad/include/
                    deps/glfw/include/
                    deps/glm/
                    deps/stb/)

file(GLOB DEPS_SOURCES    deps/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/*.h)
file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_SHADERS shaders/*.frag
                          shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Deps"    FILES ${DEPS_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${DEPS_SOURCES}
                               ${PROJECT_HEADERS} ${PROJECT_SOURCES}
                               ${PROJECT_CONFIGS}
                               ${PROJECT_SHADERS})
target_link_libraries(${PROJECT_NAME} glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})