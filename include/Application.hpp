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

    void addItem();

    void onScroll(double);

    void moveForward(double);

    void renderCrosshair();

private:
    // Private methods
    void processEvents();
    void update();
    void render();

    // Window handle
    GLFWwindow* m_window = nullptr;

    // Our renderer
    std::unique_ptr<Graphics> m_graphics;

    // Store scene objects (e.g., a list of shapes)
    // Each item is a pointer to a base Object, which could be a Cube, Sphere, etc.
    std::vector<std::unique_ptr<Object>> m_sceneObjects;

    // Track each object's transform (model matrix)
    std::vector<glm::mat4> m_objectTransforms;

    // Track each object's color
    std::vector<glm::vec4> m_objectColors;

    // Window dimensions
    int m_windowWidth  = 800;
    int m_windowHeight = 600;

    GLuint m_crosshairShader;

    // Scaling variables for the second cube
    float m_scaleFactor2 = 0.5f;         // Initial scale
    float m_scaleSpeed2  = 0.01f;        // How much to scale each frame
    bool  m_scalingUp2    = true;        // Direction of scaling

    // Utility to read text files
    std::string readFile(const std::string& filePath);
    // Compile & link a shader
    unsigned int createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);

    glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_cameraYaw = -90.0f; // Yaw starts looking down the -Z axis
    float m_cameraPitch = 0.0f; // No vertical angle initially
    float m_sensitivity = 0.1f;
    bool m_firstMouse = true;
    float m_fov = 150.0f;
    double m_lastX = 400.0; // Assuming a window width of 800
    double m_lastY = 300.0; // Assuming a window height of 600

    double m_lastAddTime = 0.0; // Timestamp of the last addition
    double m_debounceInterval = 0.2;

    bool m_leftMousePressed = false; // To track left mouse button state
    glm::vec3 m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    float m_movementSpeed = 0.1f;  // Speed for keyboard movement
    float m_scrollSpeed = 0.1f;    // Speed for trackpad movement
};
