#include "Application.hpp"

// Glad / GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

// GLM for transforms
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Include your derived shape(s)
#include "Cube.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Application::Application()
{
    // Nothing special here; we do all setup in init().
}

Application::~Application() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

bool Application::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // 2) Set OpenGL version/profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "EngineOne", nullptr, nullptr);

    if (!m_window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, m_windowWidth, m_windowHeight);

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);  


    return true;
}

void Application::run() {
    // Main loop
    while (!glfwWindowShouldClose(m_window)) {
        processEvents();
        update();
        render();
    }

    glfwTerminate();
}

void Application::processEvents() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();  
}

void Application::update() {}

void Application::render() {
    glfwSwapBuffers(m_window);
}
