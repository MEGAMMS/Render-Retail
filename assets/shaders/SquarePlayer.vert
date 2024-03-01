#version 330 core

//Positions/Coordinates
layout (location = 0) in vec2 aPos;

uniform mat4 u_trans;

void main()
{
	// Outputs the positions/coordinates of all vertices

	vec4 finalPos = vec4(aPos, 1.0, 1.0);
	finalPos = u_trans*finalPos;
	gl_Position = finalPos;
}