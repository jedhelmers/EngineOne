#include "Application.hpp"

// Include all the necessary OpenGL/GLFW headers here
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Application::Application()
    : m_window(nullptr)
{
    // Possibly initialize other members here
}

Application::~Application() {
    // Cleanup here if not already done
    // e.g. destroy window, terminate GLFW
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Application::init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // Set the required OpenGL version/profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    m_window = glfwCreateWindow(800, 600, "EngineOne", nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    // Set swap interval (optional)
    glfwSwapInterval(1); // vsync on

    // Any other one-time setup...
    // e.g. glEnable(GL_BLEND), glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_graphics = std::make_unique<Graphics>();
    
    Entity e;
    e.position = glm::vec3(0.0f, 0.0f, 0.0f);
    e.size = 1.0f;
    m_scene.push_back(e);

    return true;
}

void Application::run() {
    // Main loop
    while (!glfwWindowShouldClose(m_window)) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents() {
    // Poll for input/events
    glfwPollEvents();
    // Check for input, possibly handle close events, etc.
}

void Application::update() {
    // Game logic/updates, e.g. moving objects
}

void Application::render() {
    m_graphics->beginFrame();

    // Clear screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto& entity : m_scene) {
        m_graphics->draw(entity);
    }

    // End the frame
    m_graphics->endFrame();

    // Swap buffers
    glfwSwapBuffers(m_window);
}
