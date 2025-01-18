#pragma once

#include <memory>  // if you want to store pointers
#include <vector>  // or however you store entities

// Forward-declare or include your entity/mesh/whatever types
class Entity;

class Graphics {
public:
    Graphics();
    ~Graphics();

    // Called at the start of each frame to set up drawing
    void beginFrame();

    // Draw a single entity (or model, sprite, etc.)
    void draw(const Entity& entity);

    // End the frame
    void endFrame();

private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_shaderProgram;
    // Store your shader programs, buffers, etc. here
    // e.g. unsigned int m_defaultShader;
};
