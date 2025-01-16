#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;
out vec3 normal;
out vec3 fragmentPosition;
out vec2 texCoord;
uniform mat4 model;
layout(std140) uniform Matrices {
    mat4 view;
    mat4 perspect;
};


void main() {
    normal = normalize(vec3(transpose(inverse(model)) * vec4(Normal, 0.0)));
    fragmentPosition = vec3(model * vec4(position,1.0));
    texCoord = TexCoord;
    gl_Position = perspect * view * model * vec4(position,1.0);
}