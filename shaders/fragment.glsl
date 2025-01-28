#version 330 core
out vec4 FragColor;

// in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform sampler2D ourTexture3;

uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main()
{
    vec3 Normal = vec3(TexCoord, 0.5);
    // Sample both textures
    vec4 color1 = texture(ourTexture0, TexCoord);
    vec4 color2 = texture(ourTexture1, TexCoord);
    vec4 color3 = texture(ourTexture2, TexCoord);
    vec4 color4 = texture(ourTexture3, TexCoord);

    vec3 ambient = ambientStrength * lightColor;

    vec4 mix1 = (color1 + color2 + color3 + color4) / 4.0;
    // vec3 lightDir = normalize(lightPos - FragPos);
    // vec3 ambient = ambientStrength * lightColor * objectColor;

    // Mix the two textures with equal weighting
    // FragColor = mix(color1, color2, 0.5) * vec4(ourColor, 1.0);
    // FragColor = mix1 * vec4(ourColor, 1.0);
    // FragColor = mix1 * vec4(ambient, 1.0);
    // FragColor = vec4(ambient, 1.0);
    // float ambientStrength = 0.1;
    // vec3 ambient = ambientStrength * lightColor;
  	
    // // // diffuse 
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragColor.xyz);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = diff * lightColor;
            
    // vec3 result = (ambient + diffuse) * objectColor;
    // FragColor = vec4(result, 1.0);


    // vec3 result = ambient * objectColor;
    // FragColor = vec4(result, 1.0);
    FragColor = vec4(ambient, 1.0) * mix1;
}
