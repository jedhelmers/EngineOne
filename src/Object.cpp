#include "Object.hpp"
#include <glad/glad.h>
#include <iostream>

Object::Object()
    : VAO(0)
    , VBO(0)
{
    // We don’t generate/buffer anything yet, since derived classes may first fill 'm_vertices'.
}

Object::~Object()
{
    // Clean up GPU resources if they were created
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
}

void Object::setupBuffer() {
    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload vertex data to GPU
    // Ensure that vertices is not empty to avoid passing a null pointer
    if (!vertices.empty()) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    } else {
        // Handle empty vertex data if necessary
        // For example, you might want to log a warning
        std::cerr << "Warning: Attempting to upload empty vertex data.\n";
    }

    // Generate and bind EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Upload index data to GPU
    if (!indices.empty()) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    } else {
        // Handle empty index data if necessary
        std::cerr << "Warning: Attempting to upload empty index data.\n";
    }

    // Define vertex attributes (assuming position only)
    // Here, we're specifying that the first attribute (location 0) is for position
    // with 3 floats per vertex (x, y, z), tightly packed
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}