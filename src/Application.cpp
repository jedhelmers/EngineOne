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

// --------------
// Helper methods
// --------------
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

unsigned int Application::createShaderProgram(const std::string& vertexSource,
                                              const std::string& fragmentSource)
{
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

    // 4) Cleanup intermediate shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// --------------
// Application
// --------------
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

bool Application::init()
{
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
    // (If Graphics has its own shader creation inside, skip next steps;
    // otherwise we can pass the program from here to Graphics.)

    // 6) Load your shader files (if you want to create the shader in Application)
    std::string vertexSrc   = readFile("../shaders/vertex.glsl");
    std::string fragmentSrc = readFile("../shaders/fragment.glsl");
    if (vertexSrc.empty() || fragmentSrc.empty()) {
        std::cerr << "Shader source is empty; check file paths.\n";
        return false;
    }
    unsigned int shaderProgram = createShaderProgram(vertexSrc, fragmentSrc);

    // If your Graphics expects a "setShaderProgram(...)" you might do:
    // m_graphics->setShaderProgram(shaderProgram);

    // 7) Enable some basic GL states
    glEnable(GL_DEPTH_TEST);

    // 8) Create scene objects
    {
        // Example: create one Cube
        // Will create VAO/VBO
        auto cube = std::make_unique<Cube>();
        m_sceneObjects.push_back(std::move(cube));

        // Corresponding transform (identity)
        glm::mat4 model = glm::mat4(1.0f);
        m_objectTransforms.push_back(model);

        auto cube2 = std::make_unique<Cube>();
        m_sceneObjects.push_back(std::move(cube2));

        glm::mat4 model2 = glm::mat4(0.5f);
        m_objectTransforms.push_back(model2);
    }

    return true;
}

void Application::run()
{
    // Main loop
    while (!glfwWindowShouldClose(m_window)) {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents()
{
    glfwPollEvents();

    // If you want to close the window on Escape, for example:
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, true);
    }

    // Handle other input here...
}

void Application::update()
{
    // Example: rotate the first object in the scene
    static float angle = 0.0f;
    angle += 0.01f;

    if (!m_objectTransforms.empty()) {
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        m_objectTransforms[0] = rotation;
    }

    // If you had more objects, you'd update them likewise or store per-object transforms
}

void Application::render()
{
    // 1) Start the frame
    m_graphics->beginFrame(); 
    //   -> Typically calls glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT), etc.

    // 2) Draw each object with its transform
    for (size_t i = 0; i < m_sceneObjects.size(); i++) {
        // For this to work, your Graphics class needs something like:
        //   void draw(const Object& object, const glm::mat4& model);
        // which sets up the shader's uniforms (MVP, etc.) and calls glDrawArrays.
        //
        // Example:
        m_graphics->draw(*m_sceneObjects[i], m_objectTransforms[i]);
    }

    // 3) End the frame
    m_graphics->endFrame();

    // 4) Swap buffers
    glfwSwapBuffers(m_window);
}
