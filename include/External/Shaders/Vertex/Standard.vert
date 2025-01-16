#version 330 core
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 TexCoord;

uniform mat4 model;
layout(std140) uniform Matrices {
    mat4 view;
    mat4 perspect;
};

out vec2 texCoord;

void main() {
    gl_Position = perspect * view * model * vec4(position,1.0);
    texCoord = TexCoord;
}