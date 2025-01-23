#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
    // Sample both textures
    // vec4 color1 = texture(ourTexture, TexCoord);
    // vec4 color2 = texture(ourTexture2, TexCoord);

    // Mix the two textures with equal weighting
    // FragColor = mix(color1, color2, 0.5) * vec4(ourColor, 1.0);
    FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, TexCoord), 0.25);
}
