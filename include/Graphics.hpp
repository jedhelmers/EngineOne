#pragma once

#include <string>
#include <glm/glm.hpp>

// Forward declaration of your Object class
class Object;

class Graphics
{
public:
    Graphics();
    ~Graphics();

    // Prepares the frame (e.g., clears color/depth buffers)
    void beginFrame();

    // Draws the given Object using the specified model matrix and color
    void draw(const Object& object, const glm::mat4& modelMatrix, const glm::vec4& color);

    // Ends the frame (post-processing, etc. if desired)
    void endFrame();

private:
    unsigned int m_shaderProgram = 0;

    // Helper functions to load/compile/link shaders
    static std::string readFile(const std::string& filePath);
    static unsigned int compileShader(unsigned int type, const std::string& source);
    static unsigned int createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
};
