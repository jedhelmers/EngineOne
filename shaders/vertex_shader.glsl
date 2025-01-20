#version 330 core

layout(location = 0) in vec3 aPos;   // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 ourColor; // Pass color to fragment shader

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    ourColor = aColor; // Pass color to fragment shader
}
