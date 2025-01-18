#pragma once

#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Graphics.hpp"
#include "Object.hpp"  // or forward-declare and include "Cube.hpp" separately

// Forward-declare GLFWwindow to avoid pulling in GLFW everywhere
struct GLFWwindow;

class Application {
public:
    Application();
    ~Application();

    bool init();  // Initialize GLFW, create window, load shaders, etc.
    void run();   // Main loop

private:
    // Helper methods
    void processEvents();
    void update();
    void render();

private:
    GLFWwindow* m_window = nullptr;

    // Our renderer
    std::unique_ptr<Graphics> m_graphics;

    // Store a list of scene Objects. Each could be a Cube, Sphere, etc.
    std::vector<std::unique_ptr<Object>> m_sceneObjects;

    // Store transforms (one per object). Alternatively, you might store
    // transforms in each Object subclass.
    std::vector<glm::mat4> m_objectTransforms;

    // Window dimensions
    int m_windowWidth  = 800;
    int m_windowHeight = 600;

    // Utility to read text files
    std::string readFile(const std::string& filePath);
    // Compile & link a shader
    unsigned int createShaderProgram(const std::string& vertexSource,
                                     const std::string& fragmentSource);
};
