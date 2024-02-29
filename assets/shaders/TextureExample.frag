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
    //Zoom In:
    // TexCoordCopy = TexCoordCopy*0.05 + 0.4;
    //Zoom Out:
    TexCoordCopy = TexCoordCopy*2.;
    vec4 texture1Color = texture(texture1, TexCoordCopy);
    vec4 texture2Color = texture(texture2, TexCoordCopy);
    FragColor = mix(texture1Color, texture2Color, mix_portion);
}