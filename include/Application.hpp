#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.hpp"
#include "Texture.hpp"

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

    void addItem();

private:
    // Private methods
    void processEvents();
    void update();
    void render();

    GLFWwindow* m_window = nullptr;

    // Window dimensions
    int m_windowWidth  = 800;
    int m_windowHeight = 600;

    unsigned int shaderProgram;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    std::vector<Shader> shaders;
    std::vector<std::vector<Texture*>> textures;
};
