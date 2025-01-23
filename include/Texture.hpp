#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

class Texture {
public:
    // Constructor
    Texture(const char* path);

    // Destructor
    ~Texture();

    // Use the texture
    void Use() const;

    // Get the texture ID
    unsigned int getID() const;

    // Delete copy constructor and copy assignment to prevent accidental copies
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Implement move constructor and move assignment if needed
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

private:
    unsigned int textureID = 0; // Member variable with default initialization
};

#endif
