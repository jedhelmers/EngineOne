#pragma once
#include <vector>

class Object
{
public:
    Object();
    virtual ~Object();

    // Returns AABB in local (object) space
    // virtual AABB getLocalBounds() const = 0;

    // Called to upload vertex data to GPU (bind + buffer data + attribute setup).
    // Typically, you'd call this inside the constructor of a derived class once the
    // vertex data is known.
    void setupBuffer();

    // Bind/unbind the VAO (so we can call draw commands).
    void bind() const;
    void unbind() const;

    // Returns number of vertices (assumes 3D positions).
    // If you store vertices as (x, y, z), then each vertex is 3 floats.
    unsigned int getVertexCount() const;

protected:
    unsigned int m_vao;
    unsigned int m_vbo;

    // This holds your vertex data in CPU memory until you upload it to the GPU.
    // Typically: { x, y, z, x, y, z, x, y, z, ... } for a 3D object.
    std::vector<float> m_vertices;
};
