#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform int useTexture;
uniform sampler2D textureSlot;
uniform vec2 scale;

void main()
{
    vec2 TexCoordCopy = TexCoord*scale;
    vec4 textureColor = texture(textureSlot, TexCoordCopy);
    FragColor = mix(vec4(ourColor,1.0),textureColor,float(useTexture));
}