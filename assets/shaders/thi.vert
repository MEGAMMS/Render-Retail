#version 330 core

// Vertex Input Attributes
layout(location = 0) in vec3 a_position; // Position attribute
layout(location = 1) in vec3 a_color;    // Color attribute

// Output to Fragment Shader
out vec3 v_color;

// Uniforms (Optional, e.g., transformations)
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    // Apply transformations if uniforms are set; otherwise, pass raw position
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
    // gl_Position = vec4(a_position, 1.0);
    // Pass the vertex color to the fragment shader
    v_color = a_color;
}

