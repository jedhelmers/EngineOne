#include "Graphics.hpp"
#include <glad/glad.h>

Graphics::Graphics() {
    // 1. Create shaders, buffers, etc.

    // 2. Create VAO/VBO
    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the vertex data:
    // position attribute, index 0
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Graphics::~Graphics() {
    // Cleanup GPU resources
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void Graphics::beginFrame() {
    // Clear the screen, set viewport, etc.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::draw(const Entity& entity) {
    // Bind the VAO, set up the shader,
    // pass uniforms (transform, etc.), then draw
    // glBindVertexArray(entity.vao);
    // glDrawArrays(GL_TRIANGLES, 0, entity.vertexCount);

    // 1) Use shader program
    glUseProgram(m_shaderProgram);

    // 2) Calculate a model matrix from entity.position, entity.scale, etc.
    // e.g. using GLM:
    // glm::mat4 model = glm::translate(glm::mat4(1.0f), entity.position)
    //                * glm::scale(glm::mat4(1.0f), entity.scale);
    // pass it as a uniform:
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // 3) Bind the VAO
    glBindVertexArray(m_VAO);

    // 4) Draw the quad
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // 5) Unbind / cleanup
    glBindVertexArray(0);
}

void Graphics::endFrame() {
    // Possibly do post-processing, unbind resources, etc.
}
