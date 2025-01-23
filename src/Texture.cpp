#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"
#include <stb_image/stb_image.h>
#include <glad/glad.h>
#include <iostream>

Texture::Texture(const char* path) {
    stbi_set_flip_vertically_on_load(true); // Flip the image vertically to match OpenGL's coordinate system

    glGenTextures(1, &texture);
    std::cout << "TEXTRE: " << texture << std::endl;
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    
    if (data) {
        std::cout << "Loaded texture: " << path 
                  << " (" << width << "x" << height 
                  << ", " << nrChannels << " channels)" << std::endl;
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            std::cout << "Unsupported number of channels: " << nrChannels << std::endl;
            format = GL_RGB; // Fallback
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture at path: " << path << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

void Texture::Use() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

unsigned int Texture::getID() {
    return texture;
}