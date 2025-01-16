#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec3 colors;

uniform mat4 model;
layout(std140) uniform Matrices {
    mat4 view;
    mat4 perspect;
};

out vec3 color;

void main() {
    color = colors;
    vec3 offset = gl_InstanceID * vec3(1);
    gl_Position = perspect * view * model * vec4(position + offset,1.0);
}