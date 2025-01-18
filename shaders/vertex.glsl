#version 330 core

layout (location = 0) in vec3 aPos;

// Typically you'd have a uniform mat4 model, view, projection, 
// but let's do a single MVP matrix for simplicity.
uniform mat4 uMVP;

void main()
{
    gl_Position = uMVP * vec4(aPos, 1.0);
}
