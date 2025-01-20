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

    // 3) Upload vertex data (positions + normals)
    glBufferData(GL_ARRAY_BUFFER,
                 m_vertices.size() * sizeof(float),
                 m_vertices.data(),
                 GL_STATIC_DRAW);

    // 4) Configure position attribute (layout = 0)
    glVertexAttribPointer(
        0,                   // attribute location in the shader
        3,                   // number of components per vertex (x, y, z)
        GL_FLOAT,            // data type
        GL_FALSE,            // not normalized
        6 * sizeof(float),    // stride (6 floats per vertex)
        (void*)0              // offset from the start of the VBO data
    );
    glEnableVertexAttribArray(0);

    // 5) Configure normal attribute (layout = 1)
    glVertexAttribPointer(
        1,                   // attribute location in the shader
        3,                   // number of components per vertex (nx, ny, nz)
        GL_FLOAT,            // data type
        GL_FALSE,            // not normalized
        6 * sizeof(float),    // stride (6 floats per vertex)
        (void*)(3 * sizeof(float)) // offset (skip position)
    );
    glEnableVertexAttribArray(1);

    // 6) Unbind everything
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
    // If each vertex consists of 6 floats (position + normal)
    return static_cast<unsigned int>(m_vertices.size() / 6);
}

