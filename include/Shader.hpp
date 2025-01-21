#pragma once
#include <string>
#include <glad/glad.h>

class Shader {
    public:
        Shader(const char*, const char*);
        ~Shader();

        void Use();
        void Init(const char*, const char*);

    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;

        uint32_t programID;
};