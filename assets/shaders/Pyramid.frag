#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;   
uniform sampler2D texture2;
uniform float mix_portion;   

void main()
{
    vec2 TexCoordCopy = TexCoord;
    FragColor = vec4(ourColor,1.0);
}