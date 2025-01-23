#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture; // Correct declaration

void main()
{
    FragColor = texture(ourTexture, TexCoord); // Use the sampler2D correctly
}
