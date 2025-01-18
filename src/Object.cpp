#include "Object.hpp"
#include <glad/glad.h>
#include <iostream>

Object::Object()
    : m_vao(0)
    , m_vbo(0)
{
    // We don’t generate/buffer anything yet, since derived classes may first fill 'm_vertices'.
}

Object::~Object()
{
    // Clean up GPU resources if they were created
    if (m_vao != 0)
        glDeleteVertexArrays(1, &m_vao);
    if (m_vbo != 0)
        glDeleteBuffers(1, &m_vbo);
}

void Object::setupBuffer()
{
    // 1) Generate a VAO + VBO
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    // 2) Bind them
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // 3) Upload vertex data
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(float),
                 m_vertices.data(),
                 GL_STATIC_DRAW);

    // 4) Configure vertex attribute (layout = 0)
    //    Assuming each vertex is 3 floats: (x, y, z)
    glVertexAttribPointer(
        0,                  // attribute location in the shader
        3,                  // number of components per vertex (x, y, z)
        GL_FLOAT,           // data type
        GL_FALSE,           // not normalized
        3 * sizeof(float),  // stride (size of each vertex in bytes)
        (void*)0            // offset from the start of the VBO data
    );
    glEnableVertexAttribArray(0);

    // 5) Unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object::bind() const
{
    glBindVertexArray(m_vao);
}

void Object::unbind() const
{
    glBindVertexArray(0);
}

unsigned int Object::getVertexCount() const
{
    // If each vertex is 3 floats, totalFloats / 3 = number of vertices
    return static_cast<unsigned int>(m_vertices.size() / 3);
}
