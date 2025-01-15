#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 MVP;
uniform mat4 model;
uniform vec2 u_textureScale;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = MVP * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord * u_textureScale;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    Normal = mat3(transpose(inverse(model))) * aNormal;
}
