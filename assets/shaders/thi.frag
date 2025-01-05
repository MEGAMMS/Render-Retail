#version 330 core

// Input from Vertex Shader
in vec3 v_color;

// Output to Screen
out vec4 FragColor;

void main() {
    FragColor = vec4(v_color, 1.0); // Use vertex color with full opacity
    FragColor = vec4(1.);
}

