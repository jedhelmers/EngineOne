#version 330 core
layout (location = 0) in vec2 position;
uniform mat4 uProjection;
void main() {
    gl_Position = uProjection * vec4(position, 0.125, 0.75);
}
