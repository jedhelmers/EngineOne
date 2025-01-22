#pragma once

class Texture
{
    public:
        Texture(const char* path);
        ~Texture();

        void Use();
        unsigned int getID();

    private:
        unsigned int texture;
};