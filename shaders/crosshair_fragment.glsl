#version 330 core
out vec4 FragColor;

uniform float thickness;

void main() {
    // Thickness based on distance from center
    float distX = abs(gl_FragCoord.x - 400.0);
    float distY = abs(gl_FragCoord.y - 300.0);
    
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);

    
}
