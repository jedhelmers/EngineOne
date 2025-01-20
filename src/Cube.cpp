#include "Cube.hpp"

Cube::Cube() {
    float vertices[] = {
        // Positions         // Colors (R, G, B)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // Red  (Back face)
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  
        0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  

        // Front face (Green)
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  

        // Other faces (Blue, Yellow, Cyan, Magenta)
        // Add similar entries for left, right, top, bottom faces
    };


    m_vertices = {
    // Back face (normals: 0, 0, -1)
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  

    // Front face (normals: 0, 0, 1)
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  

    // Left face (normals: -1, 0, 0)
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  
    -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  

    // Right face (normals: 1, 0, 0)
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  

    // Bottom face (normals: 0, -1, 0)
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  

    // Top face (normals: 0, 1, 0)
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f   
};


    unsigned int indices[] = {
        0, 1, 4,  1, 5, 4,  // Back face
        1, 2, 5,  2, 6, 5,  // Right face
        2, 3, 6,  3, 7, 6,  // Front face
        3, 0, 7,  0, 4, 7,  // Left face
        4, 5, 7,  5, 6, 7,  // Top face
        0, 1, 2,  2, 3, 0   // Bottom face
    };


    setupBuffer();
}