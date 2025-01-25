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
#include "Shader.hpp"
#include "Texture.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Application::Application() {}

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
    glfwWindowHint(GLFW_DEPTH_BITS, 24);


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
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // glEnable(GL_DEPTH_TEST);  



    addItem();

    // Optional: set swap interval (VSync)
    glfwSwapInterval(1);

    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return true;
}

void Application::addItem() {
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions            // colors           // texture coords
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
        0.0f,  0.5f, 0.0f,      0.0f, 0.0f, 1.0f,   0.5f, 1.0f  // top 
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");
    shaders.push_back(shader);

    // Example (replace with your actual absolute path)
    textures.push_back(Texture("textures/wall.jpg"));
    textures.push_back(Texture("textures/balls.jpg"));
    textures.push_back(Texture("textures/Cat03.jpg"));
    textures.push_back(Texture("textures/rambo.png"));
    textures[0].Use();
    textures[1].Use();
    textures[2].Use();
    textures[3].Use();

    shaders[0].Use();
    shaders[0].setInt("ourTexture", 0);
    shaders[0].setInt("ourTexture1", 1);
    shaders[0].setInt("ourTexture2", 2);
    shaders[0].setInt("ourTexture3", 3);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
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
    glfwPollEvents();

    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }

}

void Application::update() {
    glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
    // trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.05f, 0.05f, 1.0f));

    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.1f, 0.1f, 0.1f)); 

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.50f)); 

    glm::mat4 projection;
    projection = glm::perspective((float)glfwGetTime(), 800.0f / 600.0f, 0.1f, 100.0f);

    shaders[0].setMat4("transform", view);
    shaders[0].setMat4("projection", projection);
}

void Application::render() {
    // Clear the screen
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    textures[0].Use();
    glActiveTexture(GL_TEXTURE1);
    textures[1].Use();
    glActiveTexture(GL_TEXTURE2);
    textures[2].Use();
    glActiveTexture(GL_TEXTURE3);
    textures[3].Use();

    shaders[0].Use();
    shaders[0].setInt("ourTexture", 0);
    shaders[0].setInt("ourTexture1", 1);
    shaders[0].setInt("ourTexture2", 2);
    shaders[0].setInt("ourTexture3", 3);

    // Bind VAO and draw the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind VAO for cleanliness
    glBindVertexArray(0);

    // Swap buffers
    glfwSwapBuffers(m_window);
}


