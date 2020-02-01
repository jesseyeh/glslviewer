#include "postprocessor.h"

PostProcessor::PostProcessor(const std::string &fragmentPath) {
    if (!shader_.loadFromSource(vertexSource_, GL_VERTEX_SHADER) ||
        !shader_.loadFromFile(fragmentPath, GL_FRAGMENT_SHADER)) {
        throw "Failed to create PostProcessor shader!\n";
    }

    initVAO();
    initVBO();

    // Tell OpenGL how to interpret the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), BUFFER_OFFSET(0));

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// =======
// initVAO
// =======
void PostProcessor::initVAO() {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
}

// =======
// initVBO
// =======
void PostProcessor::initVBO() {
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
}

// ====
// draw
// ====
void PostProcessor::draw(float time, int width, int height) {
    shader_.use();

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    shader_.setVec2("iResolution", width, height);
    shader_.setFloat("iTime", time);

    glBindVertexArray(0);
}

