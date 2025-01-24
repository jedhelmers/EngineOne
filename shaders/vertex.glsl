#version 330 core
layout (location = 0) in vec3 aPos;       // Position attribute
layout (location = 1) in vec3 aColor;     // Color attribute
layout (location = 2) in vec2 aTexCoord;  // Texture coordinate attribute

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
