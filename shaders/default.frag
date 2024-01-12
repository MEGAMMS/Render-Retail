#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
in float scaleForFrag;

void main()
{
	vec3 colorInverted = vec3(color.x + scaleForFrag/3, color.y+ scaleForFrag/3,  color.z+ scaleForFrag/3);
	FragColor = vec4(colorInverted, 1.0f);
}