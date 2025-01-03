#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 finalPos = vec4(aPos, 1.0);
    finalPos = projection * view * model * vec4(aPos, 1.0);
    gl_Position = finalPos;
    TexCoord = aTexCoord;
}