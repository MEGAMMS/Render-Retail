#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 MVP;
uniform mat4 model;
uniform vec3 color;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = MVP * model * vec4(aPos, 1.0);
    ourColor = color;
    TexCoord = aTexCoord;
}