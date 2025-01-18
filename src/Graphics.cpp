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

Graphics::Graphics()
{
    // 1) Create (compile/link) the shader program
    //    Adjust the paths as needed for your project.
    m_shaderProgram = createShaderProgram(
        "../shaders/vertex.glsl",
        "../shaders/fragment.glsl"
    );

    // 2) Set any default OpenGL state, if desired:
    //    e.g. glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    // 3) Potentially configure more states (blending, culling, etc.)
}

Graphics::~Graphics()
{
    // Delete the shader program if it was created
    if (m_shaderProgram) {
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
    }
}

void Graphics::beginFrame()
{
    // Clear the screen (color + depth) each frame
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::draw(const Object& object, const glm::mat4& modelMatrix)
{
    // 1) Use our shader
    glUseProgram(m_shaderProgram);

    // 2) Build or retrieve a view + projection matrix
    //    (Here we do a simple, static camera for demonstration.)
    //    In a real app, you might pass these from outside or store them in Graphics.
    glm::mat4 view = glm::lookAt(
        glm::vec3(2.0f, 2.0f, 2.0f), // camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // look at origin
        glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
    );
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),        // FOV
        800.0f / 600.0f,            // aspect ratio
        0.1f, 100.0f                // near, far planes
    );

    // Combine into MVP
    glm::mat4 mvp = projection * view * modelMatrix;

    // 3) Upload MVP to the shader uniform
    GLint mvpLoc = glGetUniformLocation(m_shaderProgram, "uMVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

    // 4) Bind the Object's VAO
    object.bind();

    // 5) Draw the object
    glDrawArrays(GL_TRIANGLES, 0, object.getVertexCount());

    // 6) Unbind
    object.unbind();
}

void Graphics::endFrame()
{
    // If you do post-processing or multiple passes, handle them here.
    // Otherwise, might be empty.
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

    // Compile
    unsigned int vertexShader   = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Link
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
