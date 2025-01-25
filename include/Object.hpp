#pragma once
#include <vector>

class Object
{
public:
    Object();
    virtual ~Object();

protected:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // Called to upload vertex data to GPU (bind + buffer data + attribute setup).
    // Typically, you'd call this inside the constructor of a derived class once the
    // vertex data is known.
    void setupBuffer();

    // This holds your vertex data in CPU memory until you upload it to the GPU.
    // Typically: { x, y, z, x, y, z, x, y, z, ... } for a 3D object.
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
