#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>


class Shader {
    public:
        Shader(const char*, const char*);
        ~Shader();

        void Use();
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setVec3(const std::string &name, const glm::vec3 &vec) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        uint32_t getID() const;

    private:
        unsigned int vertexShader;
        unsigned int fragmentShader;
        unsigned int shaderProgram;

        GLuint programID;
};