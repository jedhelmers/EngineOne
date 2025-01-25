#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include "Texture.hpp"

class RenderObjects {
public:
    // Virtual destructor in case of inheritance
    RenderObjects() = default;
    ~RenderObjects() = default;

    // Pure virtual function for rendering (implementation in .cpp or derived class)
    void render();

    // Add a new object; returns the index of the new object
    // (Implementation can be in .cpp, or inline here if you prefer)
    void addObject(
        std::vector<float>,
        std::unique_ptr<Shader> shader,
        const std::vector<Texture>& tex,
        const glm::vec3& pos,
        const glm::vec3& rot,
        const glm::vec3& scl
    );

protected:
    // Parallel arrays:
    // The element at index i in each vector corresponds to the same renderable object.

    // Vertices
    std::vector<std::vector<float>> vertices;

    // If each object owns its shader, use unique_ptr<Shader>.
    // (Or consider storing by value if Shader is a lightweight handle class.)
    std::vector<std::unique_ptr<Shader>> shaders;

    // Each object can have multiple textures.
    // This vector-of-vectors allows variable numbers of textures per object.
    std::vector<std::vector<Texture>> textures;

    // Position, rotation, scale for each object (SoA).
    // Indices match the corresponding shader/texture vector entries.
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> rotations;
    std::vector<glm::vec3> scales;
};

