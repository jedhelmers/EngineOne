#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Graphics.hpp"
#include "Object.hpp"   // or "Cube.hpp" if you want direct access to Cube

// Forward-declare GLFWwindow to avoid pulling in GLFW everywhere
struct GLFWwindow;

class Application {
public:
    Application();
    ~Application();

    // Initialize all resources (returns false if something fails)
    bool init();

    // The main loop: keep running until the user closes the window
    void run();

private:
    // Private methods
    void processEvents();
    void update();
    void render();

    GLFWwindow* m_window = nullptr;

    // Window dimensions
    int m_windowWidth  = 800;
    int m_windowHeight = 600;
};
