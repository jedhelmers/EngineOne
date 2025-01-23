#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include "Texture.hpp"

// Constructor without Variable Shadowing
Texture::Texture(const char* path) {
    glGenTextures(1, &this->textureID); // Initialize member variable
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    // Set texture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // Optional: Flip image vertically
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            std::cout << "Unsupported number of channels: " << nrChannels << std::endl;
            format = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Loaded texture: " << path << " with ID: " << this->textureID << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);
}

// Destructor
Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

// Use the texture
void Texture::Use() const {
    glBindTexture(GL_TEXTURE_2D, textureID);
}

// Get the texture ID
unsigned int Texture::getID() const {
    return textureID;
}

// Move constructor
Texture::Texture(Texture&& other) noexcept : textureID(other.textureID) {
    other.textureID = 0;
}

// Move assignment
Texture& Texture::operator=(Texture&& other) noexcept {
    if (this != &other) {
        glDeleteTextures(1, &textureID);
        textureID = other.textureID;
        other.textureID = 0;
    }
    return *this;
}
