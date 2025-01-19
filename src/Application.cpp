#include "Application.hpp"

// Glad / GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

// GLM for transforms
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Include your derived shape(s)
#include "Cube.hpp"

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->moveForward(yOffset);
    }
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
    // 1) Initialize GLFW
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

    // 3) Create window
    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "EngineOne", nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);

    // 4) Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    // Optional: set swap interval (VSync)
    glfwSwapInterval(1);

    // 5) Create and initialize Graphics
    m_graphics = std::make_unique<Graphics>();
    if (!m_graphics) {
        std::cerr << "Failed to create Graphics object!\n";
        return false;
    }

    // 6) Enable some basic GL states
    glEnable(GL_DEPTH_TEST);

    // 7) Create scene objects
    {
        addItem();
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetScrollCallback(m_window, scrollCallback);

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

void Application::onScroll(double yOffset) {
    m_fov -= static_cast<float>(yOffset);
    if (m_fov < 1.0f) m_fov = 1.0f;   // Limit zoom in
    if (m_fov > 45.0f) m_fov = 45.0f; // Limit zoom out
}

void Application::processEvents() {
    glfwPollEvents();

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }

    // Detect mouse button state
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!m_leftMousePressed) {
            m_leftMousePressed = true;
            glfwGetCursorPos(m_window, &m_lastX, &m_lastY); // Initialize mouse position
        }
    } else {
        m_leftMousePressed = false;
        m_firstMouse = true; // Reset for future drags
    }

    // Handle mouse movement when button is pressed
    if (m_leftMousePressed) {
        double xpos, ypos;
        glfwGetCursorPos(m_window, &xpos, &ypos);

        float xOffset = xpos - m_lastX;
        float yOffset = ypos - m_lastY;
        m_lastX = xpos;
        m_lastY = ypos;

        if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            // Shift + Drag = Pan
            float panSpeed = 0.01f; // Adjust for sensitivity
            m_cameraTarget.x -= xOffset * panSpeed;
            m_cameraTarget.y += yOffset * panSpeed;
        } else {
            // Drag = Zoom
            // float zoomSpeed = 0.05f;
            // m_fov -= yOffset * zoomSpeed;
            // if (m_fov < 1.0f) m_fov = 1.0f;   // Limit zoom in
            // if (m_fov > 45.0f) m_fov = 45.0f; // Limit zoom out
        }
    }

    if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_movementSpeed;
    }

    if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_movementSpeed;
    }

    if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS) {
        m_cameraPos -= m_cameraUp * m_movementSpeed;
    }

    if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_cameraPos += m_cameraUp * m_movementSpeed;
    }

    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
        double currentTime = glfwGetTime(); // Get current time
        if (currentTime - m_lastAddTime > m_debounceInterval) {
            m_lastAddTime = currentTime; // Update last action time
            addItem();
        }
    }
}

void Application::addItem() {
    // Create a new Cube
    auto cube = std::make_unique<Cube>();
    m_sceneObjects.push_back(std::move(cube));

    // Initialize its transform (identity matrix for now)
    glm::mat4 model = glm::mat4(1.0f);
    m_objectTransforms.push_back(model);

    // Assign a random color
    glm::vec4 color = glm::vec4(static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX, 1.0f);
    m_objectColors.push_back(color);

    std::cout << "Added a new item! Total items: " << m_sceneObjects.size() << std::endl;
}

void Application::update() {
    // --- Rotate the first cube ---
    static float angle = 0.0f;
    angle += 0.01f;

    if (!m_objectTransforms.empty()) {
        // Create a rotation matrix around the Y-axis
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        m_objectTransforms[0] = rotation;
    }

    // --- Dynamic Scaling of the Second Cube ---
    // Check if the second cube exists
    // if (m_objectTransforms.size() >= 2) {
    //     // Update scale factor
    //     if (m_scalingUp2) {
    //         m_scaleFactor2 += m_scaleSpeed2;
    //         if (m_scaleFactor2 >= 1.0f) {  // Maximum scale
    //             m_scalingUp2 = false;
    //         }
    //     }
    //     else {
    //         m_scaleFactor2 -= m_scaleSpeed2;
    //         if (m_scaleFactor2 <= 0.5f) {  // Minimum scale
    //             m_scalingUp2 = true;
    //         }
    //     }

    //     // Recompute the model matrix with the new scale
    //     glm::mat4 model2 = glm::mat4(1.0f);
    //     model2 = glm::scale(model2, glm::vec3(0.975f, 0.975f, 0.975f));
    //     m_objectTransforms[1] = model2;
    // }

    // --- Update Colors ---
    if (!m_objectColors.empty()) {
        // Compute color components using sine and cosine for smooth transitions
        float red   = (sin(angle) + 1.0f) / 2.0f; // Varies between 0 and 1
        float green = (cos(angle) + 1.0f) / 2.0f;
        float blue  = (sin(angle * 0.5f) + 1.0f) / 2.0f;

        // Update the color for the first cube
        m_objectColors[0] = glm::vec4(red, green, blue, 1.0f); // Alpha is 1.0f
    }

    glm::vec3 translationOffset(1.125f, 0.0f, 0.0f); // Adjust spacing as needed

    for (size_t i = 0; i < m_objectTransforms.size(); ++i) {
        // Start with the identity matrix
        glm::mat4 model = glm::mat4(1.0f);

        // Translate each object by an increasing multiple of the offset
        glm::vec3 translation = translationOffset * static_cast<float>(i);
        model = glm::translate(model, translation);

        // Update the object's transform
        m_objectTransforms[i] = model;
    }
}

void Application::render() {
    m_graphics->beginFrame();

    glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    for (size_t i = 0; i < m_sceneObjects.size(); i++) {
        glm::mat4 mvp = projection * view * m_objectTransforms[i];
        m_graphics->draw(*m_sceneObjects[i], mvp, m_objectColors[i]);
    }

    m_graphics->endFrame();
    glfwSwapBuffers(m_window);
}

void Application::moveForward(double scrollOffset) {
    m_cameraPos += m_cameraFront * static_cast<float>(scrollOffset) * m_scrollSpeed;
}


// Helper method implementations

std::string Application::readFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filePath << std::endl;
        return {};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Application::createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    // 1) Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vsrc = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vsrc, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 2) Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsrc = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fsrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 3) Link shaders into a program
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // 4) Cleanup shaders (no longer needed once linked)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
