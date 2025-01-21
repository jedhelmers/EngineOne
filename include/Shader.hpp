#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
    public:
        Shader(const std::string&, const std::string&);
        ~Shader();

        void Use();

    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;

        uint32_t programID;
};