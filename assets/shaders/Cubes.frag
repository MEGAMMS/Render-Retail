#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D cubeFace;

out vec4 FragColor;

void main()
{
    // vec2 TexCoordCopy = TexCoord* float(cubeFace);
    // FragColor = vec4(TexCoordCopy,0.0,1.0);
    vec4 textColor =  texture(cubeFace,TexCoord);
    FragColor = textColor;
}