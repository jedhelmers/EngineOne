#include "Graphics.hpp"

// Include GLAD (or your OpenGL loader) + any standard libs
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

// For transformations & matrix math
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

// Include your Object header to access bind(), unbind(), getVertexCount()
#include "Object.hpp"

Graphics::Graphics() {
    // 1) Create (compile/link) the shader program
    // Adjust the paths as needed for your project.
    m_shaderProgram = createShaderProgram(
        "../shaders/vertex.glsl",
        "../shaders/fragment.glsl"
    );

    if (m_shaderProgram == 0) {
        std::cerr << "Failed to create shader program." << std::endl;
    }

    // 2) Set any default OpenGL state, if desired:
    glEnable(GL_DEPTH_TEST);

    // 3) Potentially configure more states (blending, culling, etc.)
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Graphics::~Graphics() {
    // Delete the shader program if it was created
    if (m_shaderProgram) {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}

void Graphics::beginFrame() {
    // Clear the screen (color + depth) each frame
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::draw(const Object& object, const glm::mat4& mvp, const glm::vec4& color) {
    glUseProgram(m_shaderProgram);

    // Upload MVP matrix
    GLint mvpLoc = glGetUniformLocation(m_shaderProgram, "uMVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    // Upload color
    GLint colorLoc = glGetUniformLocation(m_shaderProgram, "uColor");
    glUniform4fv(colorLoc, 1, glm::value_ptr(color));

    // Bind and draw object
    object.bind();
    glDrawArrays(GL_TRIANGLES, 0, object.getVertexCount());
    object.unbind();
}

void Graphics::endFrame()
{
    // If you do post-processing or nothing
    // Currently empty
}

// ----------------------------------------------------------------------------
// STATIC HELPER FUNCTIONS
// ----------------------------------------------------------------------------

std::string Graphics::readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return {};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Graphics::compileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader Compilation Failed:\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int Graphics::createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
    // Read sources
    std::string vertexSource   = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);

    if (vertexSource.empty() || fragmentSource.empty()) {
        std::cerr << "Vertex/Fragment shader file is empty or not found." << std::endl;
        return 0;
    }

    // Compile shaders
    unsigned int vertexShader   = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Link shaders into a program
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader Program Linking Failed:\n" << infoLog << std::endl;
    }

    // Cleanup shaders (no longer needed once linked)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
