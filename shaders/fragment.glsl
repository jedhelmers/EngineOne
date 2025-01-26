#version 330 core
out vec4 FragColor;

// in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D ourTexture3;

void main()
{
    // Sample both textures
    vec4 color1 = texture(ourTexture0, TexCoord);
    vec4 color2 = texture(ourTexture1, TexCoord);
    vec4 color3 = texture(ourTexture2, TexCoord);
    vec4 color4 = texture(ourTexture3, TexCoord);

    vec4 mix1 = (color1 + color2 + color3 + color4) / 4.0;

    // Mix the two textures with equal weighting
    // FragColor = mix(color1, color2, 0.5) * vec4(ourColor, 1.0);
    // FragColor = mix1 * vec4(ourColor, 1.0);
    FragColor = mix1;
}
