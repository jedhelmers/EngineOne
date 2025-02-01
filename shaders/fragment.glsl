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

    vec4 mix1 = (color1 + color2 + color3 + color4) / 4.0;
    
    vec3 ambient = ambientStrength * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - vec3(TexCoord, 0.0));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;

    // FragColor = vec4(ambient, 1.0) * mix1;
    FragColor = normalize(vec4(result, 1.0) * mix1);
}


// #version 330 core
// out vec4 FragColor;

// in vec3 Normal;  
// in vec3 FragPos;  
  
// uniform vec3 lightPos; 
// uniform vec3 lightColor;
// uniform vec3 objectColor;

// void main()
// {
//     // ambient
//     float ambientStrength = 0.1;
//     vec3 ambient = ambientStrength * lightColor;
  	
//     // diffuse 
//     vec3 norm = normalize(Normal);
//     vec3 lightDir = normalize(lightPos - FragPos);
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = diff * lightColor;
            
//     vec3 result = (ambient + diffuse) * objectColor;
//     FragColor = vec4(result, 1.0);
// } 