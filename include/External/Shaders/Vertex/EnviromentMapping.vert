#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
layout(std140) uniform Matrices {
    mat4 view;
    mat4 perspect;
};

out FragmentIn {
    vec3 normal;
    vec3 fragmentPosition;
} fragin;


void main() {
    fragin.normal = vec3( transpose(inverse(model)) * vec4(normal, 0.0) );
    fragin.fragmentPosition = vec3(model * vec4(position,1.0));
    gl_Position = perspect * view * model * vec4(position,1.0);
}