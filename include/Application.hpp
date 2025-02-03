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
    void addLight();

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
    std::vector<GLuint> VAOs;
    std::vector<GLuint> VBOs;
    std::vector<GLuint> EBOs;

    std::vector<Shader*> shaders;
    std::vector<std::vector<Texture*>> textures;


    // std::vector<unsigned int> LIGHT_VAOs;
    // std::vector<unsigned int> LIGHT_VBOs;
    // std::vector<unsigned int> LIGHT_EBOs;

    // std::vector<Shader*> light_shaders;
    Shader* lightingShader;
    Shader* lightCubeShader;
    GLuint VBO, containerVAO, lightVAO;

    GLuint diffuseMap;
    GLuint specularMap;
};
