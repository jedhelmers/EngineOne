#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>


class Shader {
    public:
        Shader(const char*, const char*);
        ~Shader();

        void Use();
        void SetValue(const std::string&, glm::vec3 value);

    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;

        uint32_t programID;
};